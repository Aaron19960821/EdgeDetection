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

	smallb = cv::Mat::zeros(210, 210, CV_8U);
	smallg = cv::Mat::zeros(210, 210, CV_8U);
	smallr = cv::Mat::zeros(210, 210, CV_8U);

	cv::namedWindow("img", 1);
	cv::namedWindow("dst", 1);
	cv::setMouseCallback("img", &cv::imgOnMouse, (void*)this);
	initShow();
	cv::waitKeyEx(0);
}

void display::initShow()
{
	reimage = rescale28U(originPic);
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
	std::cout << im.rows << std::endl;
}

void display::reframe()
{
	for(auto pi : edgeMapTmp)
	{
		r.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		g.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
		b.at<uchar>(pi.first, pi.second) = reimage.at<uchar>(pi.first, pi.second);
	}
	edgeMapTmp.clear();

	cv::Mat channels[3];
	cv::Mat im;
	channels[0] = b;
	channels[1] = g;
	channels[2] = r;
	cv::merge(channels, 3, im);
	cv::imshow("img", im);

	cv::Mat smallim;
	channels[0] = smallb;
	channels[1] = smallg;
	channels[2] = smallr;
	cv::merge(channels, 3, smallim);
	cv::imshow("dst", smallim);
}

void display::readAnnotation()
{
	std::ifstream ifs;
	ifs.open(annotationPath, std::ifstream::in);

	assert(ifs.is_open());

	int tmpx;
	int tmpy;
	while(ifs >> tmpx >> tmpy)
	{
		edgeMap.push_back(std::make_pair(tmpx, tmpy));
	}
	ifs.close();
	return;
}

