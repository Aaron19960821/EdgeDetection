/*************************************************************************
    > File Name: main.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 20:42:04 2018
 ************************************************************************/

#include<iostream>
#include<opencv2/highgui.hpp>
#include<utility>
#include<assert.h>
#include<string.h>

#include"fitsutils.h"
#include"imageutils.h"
#include"cannydetector.h"
#include"display.h"
using namespace std;

int main(int argc, char** argv)
{

	char* file = "~/Downloads/data1/N1485951682_2.fits";
	cout << getFitsname(file) << endl;
	cout << getFitsDir(file) << endl;

	assert(argc > 2);
	if(strcmp(argv[1], "-d") == 0)
	{
		cannyDetector detector(120, 120.0*3);
		detector.detectFromBatch(argv[2]);
	}
	else if(strcmp(argv[1], "-p") == 0)
	{
		display screen(argv[2]);
	}

	char* filename = "./N1466586614_1.fits";
	cv::Mat image = readFits(filename, 0);
	cv::Mat reimage = rescale28U(image);
	cv::Mat edge = canny(reimage, 125, 125*2);

	cv::Mat r;
	reimage.copyTo(r);
	cv::Mat g(reimage);
	reimage.copyTo(g);
	cv::Mat b(reimage);
	reimage.copyTo(b);

	pair<int,int> xaxis(edge.rows, -1);
	pair<int,int> yaxis(edge.cols, -1);
	for(int i=0;i<edge.rows;i++)
	{
		for(int j=0;j<edge.cols;j++)
		{
			uchar pixel = edge.at<uchar>(i,j);
			if(pixel > 0)
			{
				b.at<uchar>(i,j) = 0;
				g.at<uchar>(i,j) = 0;
				r.at<uchar>(i,j) = 255;
			}
		}
	}

	cv::Mat im;
	cv::Mat channels[3];
	channels[0] = b;
	channels[1] = g;
	channels[2] = r;
	cv::merge(channels, 3, im);

	cout << "aa" << endl;
	cv::namedWindow("hello", CV_WINDOW_NORMAL);
	cv::imshow("hello", im);
	cv::resizeWindow("hello", 200, 200);
	cv::waitKey(100000000);

	return 0;
}

