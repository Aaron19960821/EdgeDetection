/*************************************************************************
    > File Name: display.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Sat May 12 20:08:23 2018
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include"fitsutils.h"
#include"fitsmarker.h"
#include"imageutils.h"
#include"display.h"
#include"displayUtils.h"

display::display(const char* filePath)
{
	picPath = std::string(filePath);
	std::string imageName = getFitsname(filePath);
	std::string imageDir = getFitsDir(filePath);

	originPic = readFits(filePath, 1);
	annotationPath = imageDir + "Annotation/" + imageName + ".txt";
	readAnnotation();

	reimage = rescale28U(originPic);
	larger = largeDisplay(21, 21, 10);
	unmarkLarger = largeDisplay(21, 21, 10);


	cv::namedWindow("img", 1);
	cv::namedWindow("dst", 1);
	cv::namedWindow("unmarkedDst", 1);
	cv::setMouseCallback("img", &cv::imgOnMouse, (void*)this);
	initShow();
	while(1)
	{
		int c = cv::waitKey(0);
		int res = cv::imgOnKeyboard(c, (void*)this);
		if(res < 0)
		{
			break;
		}
	}
}

void display::initShow()
{
	reimage.copyTo(b);
	reimage.copyTo(g);
	reimage.copyTo(r);

	for(auto pi : edgeMap)
	{
		r.at<uchar>(pi.first, pi.second) = 255;
		b.at<uchar>(pi.first, pi.second) = 0;
		g.at<uchar>(pi.first, pi.second) = 0;
	}

	cv::Mat channels[3];
	cv::Mat im;
	channels[0] = b;
	channels[1] = g;
	channels[2] = r;
	cv::merge(channels, 3, im);
	cv::imshow("img", im);
}

/*
 * Eliminate all edge points inside the ROI
 */

void display::keepEdge(int xmin, int xmax, int ymin, int ymax)
{
	int eliminateEdgeNum = 0;
	std::vector<std::pair<int,int>> newEdgeMap;
	for(auto pi : edgeMapTmp)
	{
		if(pi.first >= ymin && pi.first <= ymax && pi.second >= xmin && pi.second <= xmax)
		{
			newEdgeMap.push_back(pi);
		}
		else
		{
			eliminateEdgeNum++;
		r.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		g.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		b.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		}
	}
	std::cout << "Eliminate " << eliminateEdgeNum << std::endl;
	edgeMapTmp = newEdgeMap;
	return;
}

/*
 * Eliminate all edge points inside ROI
 */
void display::eliminateEdge(int xmin, int xmax, int ymin, int ymax)
{
	int eliminateEdgeNum = 0;
	std::vector<std::pair<int,int>> newEdgeMap;
#if TEST
	std::cout << "Hh" << std::endl;
#endif
	for(auto pi : edgeMapTmp)
	{
		if(pi.first >= ymin && pi.first <= ymax && pi.second >= xmin && pi.second <= xmax)
		{
			eliminateEdgeNum++;
			r.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
			g.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
			b.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		}
		else
		{
			newEdgeMap.push_back(pi);
		}
	}
	std::cout << "Eliminate " << eliminateEdgeNum << std::endl;
	edgeMapTmp = newEdgeMap;
	return;
}

void display::reframe()
{
	cv::Mat channels[3];
	cv::Mat im;
	channels[0] = b;
	channels[1] = g;
	channels[2] = r;
	cv::merge(channels, 3, im);
	cv::imshow("img", im);

	cv::Mat smallim;
	channels[0] = larger.b;
	channels[1] = larger.g;
	channels[2] = larger.r;
	cv::merge(channels, 3, smallim);
	cv::imshow("dst", smallim);

	cv::Mat unmarkSmallIm;
	channels[0] = unmarkLarger.b;
	channels[1] = unmarkLarger.g;
	channels[2] = unmarkLarger.r;
	cv::merge(channels, 3, unmarkSmallIm);
	cv::imshow("unmarkedDst", unmarkSmallIm);
}

void display::readAnnotation()
{
	std::ifstream ifs;
	ifs.open(annotationPath, std::ifstream::in);

	if(!ifs.is_open())
	{
		return;
	}

	int tmpx;
	int tmpy;
	while(ifs >> tmpx >> tmpy)
	{
		edgeMap.push_back(std::make_pair(tmpx, tmpy));
		edgeMapTmp.push_back(std::make_pair(tmpx, tmpy));
	}
	ifs.close();
	return;
}

void display::saveAnnotation()
{
	std::ofstream ofs;
	ofs.open(annotationPath, std::ofstream::out);

	assert(ofs.is_open());

	for(auto pi : edgeMapTmp)
	{
		ofs << pi.first << " " << pi.second << std::endl;
	}
	ofs.close();
	return;
	
}

largeDisplay::largeDisplay(int w, int h, int dim)
{
	r = cv::Mat(w*dim, h*dim, CV_8U);
	g = cv::Mat(w*dim, h*dim, CV_8U);
	b = cv::Mat(w*dim, h*dim, CV_8U);
	this -> w = w;
	this -> h = h;
	this -> dim = dim;
}

int largeDisplay::geth()
{
	return h;
}

int largeDisplay::getw()
{
	return w;
}

int largeDisplay::getdim()
{
	return dim;
}


/*
 * Refresh largeDisplay with given overall rgb matrics
 */
void largeDisplay::refresh(cv::Mat bb, cv::Mat gg, cv::Mat rr)
{
	int d = std::max(y - h/2, 0);
	d = std::min(d, bb.rows - h);
	int l = std::max(x - w/2, 0);
	l = std::min(l, bb.cols - w);
	for(int i=d; i<d+h; i++)
		{
			for(int j=l; j<l+w; j++)
			{
				for(int k=(i-d)*dim; k<(i-d)*dim+dim; k++)
				{
					for(int p=(j-l)*dim; p<(j-l)*dim+dim; p++)
					{
						b.at<uchar>(k,p) = bb.at<uchar>(i,j);
						g.at<uchar>(k,p) = gg.at<uchar>(i,j);
						r.at<uchar>(k,p) = rr.at<uchar>(i,j);
						//the center of larger display set to blue
						if(i == y && j == x)
						{
							b.at<uchar>(k,p) = 255;
							g.at<uchar>(k,p) = 0;
							r.at<uchar>(k,p) = 0;
						}
					}
				}
			}
		}
}

largeDisplay::largeDisplay()
{
	w = 21;
	h = 21;
	dim = 10;
}

int largeDisplay::getx()
{
	return x;
}

int largeDisplay::gety()
{
	return y;
}

void largeDisplay::setx(int newx, int maxx)
{
	if(newx < 0)newx = 0;
	else if(newx >= maxx) newx = maxx - 1;
	x = newx;
}

void largeDisplay::sety(int newy, int maxy)
{
	if(newy < 0)newy = 0;
	else if(newy >= maxy) newy = maxy - 1;
	y = newy;
}

