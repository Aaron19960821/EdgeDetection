/*************************************************************************
    > File Name: cannydetector.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Thu May 10 22:42:23 2018
 ************************************************************************/


#include<iostream>
#include<cstdio>
#include<string>
#include<string.h>
#include<cmath>
#include<assert.h>
#include<utility>
#include<vector>
#include<fstream>

#include"imageutils.h"
#include"fitsmarker.h"
#include"fitsutils.h"
#include"cannydetector.h"

cannyDetector::cannyDetector()
{
	thresh1 = 120;
	thresh2 = 120*2 + 20;
}

cannyDetector::~cannyDetector()
{
}

cannyDetector::cannyDetector(double thresh11, double thresh22)
{
	thresh1 = thresh11;
	thresh2 = thresh22;
}

cv::Mat cannyDetector::getEdgeFromSingleImage(cv::Mat src)
{
	cv::Mat reimage = rescale28U(src);
	return canny(reimage, thresh1, thresh2);
}

void cannyDetector::detectFromSingleImage(char* filename)
{
	std::cout << "Processing " << filename << std::endl;
	std::string file(filename);
	cv::Mat image = readFits(file.c_str(), 0);
	cv::Mat edge = getEdgeFromSingleImage(image);
	std::vector<std::pair<int,int> >edgeMap;
	for(int i=0; i<edge.rows; i++)
	{
		for(int j=0; j<edge.cols;j++)
		{
			uchar pixel = edge.at<uchar>(i,j);
			if(pixel > 0)
			{
				edgeMap.push_back(std::make_pair(i,j));
			}
		}
	}
	std::string dir(getFitsDir(filename));
	std::string outfilename(getFitsname(filename));
	outfilename = dir + "Annotation/" + outfilename + ".txt";
	dumpEdgeToFile(edgeMap, outfilename.c_str());
}

/*
 * Perform canny to a batch of images.
 * filename is the path to the image list
 */
void cannyDetector::detectFromBatch(char* filename)
{
	char buf[256];
	std::ifstream ifs;
	ifs.open(filename, std::ifstream::in);

	assert(ifs.is_open());

	while(ifs.getline(buf, 256))
	{
		std::cout << "Processing " << buf << std::endl;
		
		std::string file(buf);
		cv::Mat image = readFits(file.c_str(), 0);
		cv::Mat edge = getEdgeFromSingleImage(image);
		std::vector<std::pair<int,int> >edgeMap;
		for(int i=0; i<edge.rows; i++)
		{
			for(int j=0; j<edge.cols;j++)
			{
				uchar pixel = edge.at<uchar>(i,j);
				if(pixel > 0)
				{
					edgeMap.push_back(std::make_pair(i,j));
				}
			}
		}
		std::string dir(getFitsDir(buf));
		std::string filename(getFitsname(buf));
		filename = dir + "Annotation/" + filename + ".txt";
		dumpEdgeToFile(edgeMap, filename.c_str());
	}
	ifs.close();
	return;
}

void cannyDetector::dumpEdgeToFile(std::vector<std::pair<int,int> >edgeMap, const char* filename)
{
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out);

	assert(ofs.is_open());

	for(auto pi : edgeMap)
	{
		ofs << pi.first << " " << pi.second << std::endl;
	}
	ofs.close();
	return;
}
