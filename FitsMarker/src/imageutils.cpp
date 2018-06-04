/*************************************************************************
    > File Name: imageutils.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Thu May 10 19:36:04 2018
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<string>
#include<utility>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<cmath>

#define TEST 0

std::pair<double, double> getRange(cv::Mat src)
{
	std::pair<float, float> res(1e10, -1);

	for(int i=0; i<src.rows; i++)
	{
		for(int j=0; j<src.cols; j++)
		{
			float pixel = src.at<float>(i,j);
			res.first = fmin(pixel, res.first);
			res.second = fmax(pixel, res.second);
		}
	}
	return res;
}

cv::Mat rescale28U(cv::Mat src)
{
	auto originScale = getRange(src);
	cv::Mat res(src.rows, src.cols, CV_8UC1);
	float scale = 255.0/(originScale.second - originScale.first);
#if TEST
	float maxPixel = -1.0;
#endif

	for(int i=0; i<src.rows; i++)
	{
		for(int j=0; j<src.cols; j++)
		{
			float scaletmp = (src.at<float>(i, j) - originScale.first) * scale;
			uchar pixel = std::floor(scaletmp);
#if TEST
			maxPixel = fmax(scaletmp, maxPixel);
			if(pixel > 200) std::cout << i << " " << j << std::endl;
#endif
			res.at<uchar>(i,j) = pixel;
		}
	}
#if TEST
	std::cout << maxPixel << std::endl;
	std::cout << src.rows << std::endl;
	std::cout << src.cols << std::endl;
#endif
	return res;
}

cv::Mat canny(cv::Mat src, double thresh1, double thresh2)
{
	cv::Mat res(src.rows, src.cols, CV_8UC1);
	cv::Canny(src, res, thresh1, thresh2, 3, true);
	return res;
}

