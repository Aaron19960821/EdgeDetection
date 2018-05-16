/*************************************************************************
    > File Name: displayUtils.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Tue May 15 21:27:57 2018
 ************************************************************************/

#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>
#include"displayUtils.h"
#include"display.h"

void cv::imgOnMouse(int event, int x, int y, int flags, void* ustc)
{
	display* screen = (display*)ustc;

	if(event == CV_EVENT_LBUTTONDOWN)
	{
		screen -> lpressed = true;
		screen -> tmpx = x;
		screen -> tmpy = y;
	}
	else if(event == CV_EVENT_LBUTTONUP && flags == 9)
	{
		if(screen -> lpressed)
		{
			std::cout << "Set ROI, eliminate all edge outside ROI" << std::endl;
			if(x < screen -> tmpx)
			{
				std::swap(x, screen -> tmpx);
			}
			if(y < screen -> tmpy)
			{
				std::swap(y, screen -> tmpy);
			}
			screen -> keepEdge(screen->tmpx, x, screen->tmpy, y);
			screen -> lpressed = false;
			screen -> reframe();
		}
	}
	else if(event == CV_EVENT_LBUTTONUP)
	{
		std::cout << flags << std::endl;
		if(screen -> lpressed)
		{
			if(x == screen -> tmpx && y == screen -> tmpy)
			{
				int isMarked = false;
				std::vector<std::pair<int,int>> newEdgeMap;
				for(auto pi : screen -> edgeMapTmp)
				{
					if(pi.first == y && pi.second == x)
					{
						isMarked = true;
					}
					else
					{
						newEdgeMap.push_back(pi);
					}
				}
				if(isMarked)
				{
					screen -> b.at<uchar>(y, x) = screen -> reimage.at<uchar>(y, x);
					screen -> g.at<uchar>(y, x) = screen -> reimage.at<uchar>(y, x);
					screen -> r.at<uchar>(y, x) = screen -> reimage.at<uchar>(y, x);
					std::cout << "Unmark a pixel at (" << x << "," << y << ")" << std::endl;
				}
				else
				{
					screen -> b.at<uchar>(y, x) = 0;
					screen -> r.at<uchar>(y, x) = 255;
					screen -> g.at<uchar>(y, x) = 0;
					std::cout << "Mark a pixel at (" << x << "," << y << ")" << std::endl;
					newEdgeMap.push_back(std::make_pair(y, x));
				}
				screen -> edgeMapTmp = newEdgeMap;
				screen -> reframe();
			}
		}
	}
	else if(event == CV_EVENT_MOUSEMOVE)
	{
		int l;
		int r;
		int u;
		int d;
		l = max(0, x - 10);
		r = l + 20;
		d = max(0, y - 10);
		u = d + 20;
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r, d, l, x, y);
		screen -> reframe();
	}
}

