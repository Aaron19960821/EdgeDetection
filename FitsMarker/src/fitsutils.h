/*************************************************************************
    > File Name: fitsutils.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 19:18:36 2018
 ************************************************************************/

#ifndef FITSUTILS_H
#define FITSUTILS_H

#include<iostream>
#include<cstring>
#include<string>
#include<fitsio.h>
#include<opencv2/highgui.hpp>

cv::Mat readFits(const char* filename, int mode);
std::string getFitsname(const char* fitsPath);
std::string getFitsDir(const char* fitspath);

#endif

