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
		cv::Mat originPic;
		cv::Mat reimage;
		std::string picPath;
		std::string annotationPath;
		void readAnnotation();
		//void imgOnMouse(int event, int x, int y, int flags, void* ustc);
	public:
		bool lpressed;
		bool rpressed;
		int tmpx;
		int tmpy;
		cv::Mat smallb;
		cv::Mat smallg;
		cv::Mat smallr;
		cv::Mat r;
		cv::Mat g;
		cv::Mat b;

		std::vector<std::pair<int,int> > edgeMapTmp; 
		std::vector<std::pair<int,int> > edgeMap;
		display(const char* filePath);
		void reframe();
		void initShow();
};

#endif

