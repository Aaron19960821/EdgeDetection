/*************************************************************************
    > File Name: display.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Sat May 12 20:08:34 2018
 ************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
#include<opencv2/highgui.hpp>

class display
{
	private:
		cv::Mat r;
		cv::Mat g;
		cv::Mat b;
		cv::Mat im;
		cv::Mat originPic;
		std::vector<std::pair<int,int> > edgeMap;
		std::vector<std::pair<int,int> > edgeMapTmp; 
		std::string picPath;
		std::string annotationPath;
		void readAnnotation();
		void initShow();
	public:
		display(const char* filePath);
};

#endif

