/*************************************************************************
    > File Name: imageutils.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 22:15:53 2018
 ************************************************************************/

#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include<iostream>
#include<string>
#include<opencv2/highgui.hpp>
#include<utility>

cv::Mat rescale28U(cv::Mat src);
cv::Mat canny(cv::Mat src, double thresh1, double thresh2);
std::pair<float, float> getRange(cv::Mat src);

#endif

