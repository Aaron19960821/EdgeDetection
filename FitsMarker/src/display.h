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
		void setx(int newx, int maxx);
		void sety(int newy, int maxy);
		int getx();
		int gety();
		int getw();
		int geth();
		int getdim();
		void refresh(cv::Mat bb, cv::Mat gg, cv::Mat rr);
		cv::Mat r;
		cv::Mat g;
		cv::Mat b;
	private:
		int x;
		int y;
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
		largeDisplay unmarkLarger;

		std::vector<std::pair<int,int> > edgeMapTmp; 
		std::vector<std::pair<int,int> > edgeMap;
		display(const char* filePath);
		void reframe();
		void initShow();
		void keepEdge(int xmin, int xmax, int ymin, int ymax);
		void eliminateEdge(int xmin, int xmax, int ymin, int ymax);
		void saveAnnotation();
};

#endif

