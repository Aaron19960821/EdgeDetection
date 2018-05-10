/*************************************************************************
    > File Name: main.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 20:42:04 2018
 ************************************************************************/

#include<iostream>
#include<opencv2/highgui.hpp>
#include<utility>

#include"fitsutils.h"
#include"imageutils.h"
using namespace std;

int main(int argc, char** argv)
{
	char* filename = "./N1466586614_1.fits";
	cv::Mat image = readFits(filename, 0);
	cv::Mat reimage = rescale28U(image);
	cv::Mat edge = canny(reimage, 125, 125*2);

	pair<int,int> xaxis(edge.rows, -1);
	pair<int,int> yaxis(edge.cols, -1);
	for(int i=0;i<edge.rows;i++)
	{
		for(int j=0;j<edge.cols;j++)
		{
			uchar pixel = edge.at<uchar>(i,j);
			if(pixel > 0)
			{
				xaxis.first = min(xaxis.first, i);
				xaxis.second = max(xaxis.second, i);
				yaxis.first = min(yaxis.first, j);
				yaxis.second = max(yaxis.second, j);
			}
		}
	}

	return 0;
}

