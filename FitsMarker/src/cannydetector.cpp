/*************************************************************************
    > File Name: cannydetector.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Thu May 10 22:42:23 2018
 ************************************************************************/


#include<iostream>
#include<cstdio>
#include<string>
#include<assert.h>
#include<utility>
#include<vector>

#include"imageutils.h"
#include"fitsutils.h"

cannyDetector::cannyDetector()
{
	this->thresh1 = 120;
	this->thresh2 = 120*2 + 20;
}

cannyDetector::cannyDetector(double thresh1, double thresh2)
{
	this->thresh1 = thresh1;
	this->thresh2 = thresh2;
}

cv::Mat cannyDetector::detectFromSingleImage(cv::Mat src)
{
	cv::Mat reimage = rescale28U(src);
	return canny(reimage, thresh1, thresh2);
}

void cannyDetector::detectFromBatch(char* filename)
{
	char buf[256];
	std::ifstream ifs;
	ifs.open(filename, std::ifstream::in);

	assert(ifs.is_open());

	while(ifs.getline(buf, 256))
	{
		cv::Mat image = readFits(buf, 0);
		cv::Mat edge = detectFromSingleImage(image, self.thresh1, self.thresh2);
		std::vector<pair<int,int> >edgeMap;
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
	}
}
