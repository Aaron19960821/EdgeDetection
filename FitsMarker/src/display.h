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

class largeDisplay
{
	public:
		largeDisplay(int w, int h, int dim);
		largeDisplay();
		int getw();
		int geth();
		int getdim();
		void refresh(cv::Mat bb, cv::Mat gg, cv::Mat rr, int d, int l, int x, int y);
		cv::Mat r;
		cv::Mat g;
		cv::Mat b;
	private:
		int w;
		int h;
		int dim;
};


class display
{
	private:
		cv::Mat originPic;
		std::string picPath;
		std::string annotationPath;
		void readAnnotation();
		//void imgOnMouse(int event, int x, int y, int flags, void* ustc);
	public:
		bool lpressed;
		bool rpressed;
		int tmpx;
		int tmpy;
		cv::Mat reimage;
		cv::Mat r;
		cv::Mat g;
		cv::Mat b;
		largeDisplay larger;

		std::vector<std::pair<int,int> > edgeMapTmp; 
		std::vector<std::pair<int,int> > edgeMap;
		display(const char* filePath);
		void reframe();
		void initShow();
		void keepEdge(int xmin, int xmax, int ymin, int ymax);
		void saveAnnotation();
};

#endif

