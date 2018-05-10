/*************************************************************************
    > File Name: imageutils.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Thu May 10 19:36:04 2018
 ************************************************************************/

#include<iostream>
#include<string>
#include<utility>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<cmath>

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
	cv::Mat res(src.rows, src.cols, CV_8U);
	float scale = 255.0/(originScale.second - originScale.first);
	float maxx = -1.0;

	for(int i=0; i<src.rows; i++)
	{
		for(int j=0; j<src.cols; j++)
		{
			float scaletmp = (src.at<float>(i, j) - originScale.first) * scale;
			maxx = fmax(scaletmp, maxx);
			uchar pixel = std::floor(scaletmp);
			res.at<uchar>(i,j) = pixel;
		}
	}
	std::cout << maxx << std::endl;
	return res;
}

cv::Mat canny(cv::Mat src, double thresh1, double thresh2)
{
	cv::Mat res(src.rows, src.cols, CV_8U);
	cv::Canny(src, res, thresh1, thresh2, 3, true);
	return res;
}

