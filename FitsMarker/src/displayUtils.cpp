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

int cv::imgOnKeyboard(int flags, void* ustc)
{
	display* screen = (display*)ustc;
	int screenWidth = screen -> g.cols;
	int screenHeight = screen -> g.rows;
	if(flags == FITSMARKER_ESC)
	{
		return -1;
	}
	else if(flags == FITSMARKER_LEFT)
	{
		screen -> larger.setx(screen -> larger.getx()-1, screenWidth);
		screen -> unmarkLarger.setx(screen -> unmarkLarger.getx()-1, screenWidth);
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
		screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
		screen -> reframe();
	}
	else if(flags == FITSMARKER_RIGHT)
	{
		screen -> larger.setx(screen -> larger.getx()+1, screenWidth);
		screen -> unmarkLarger.setx(screen -> unmarkLarger.getx()+1, screenWidth);
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
		screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
		screen -> reframe();
	}
	else if(flags == FITSMARKER_UP)
	{
		screen -> larger.sety(screen -> larger.gety()-1, screenHeight);
		screen -> unmarkLarger.sety(screen -> unmarkLarger.gety()-1, screenHeight);
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
		screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
		screen -> reframe();
	}
	else if(flags == FITSMARKER_DOWN)
	{
		screen -> larger.sety(screen -> larger.gety()+1, screenHeight);
		screen -> unmarkLarger.sety(screen -> unmarkLarger.gety()+1, screenHeight);
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
		screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
		screen -> reframe();
	}
	else if(flags == FITSMARKER_ENTER)
	{
		int y = screen -> larger.gety();
		int x = screen -> larger.getx();
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
	return 0;
}

void cv::imgOnMouse(int event, int x, int y, int flags, void* ustc)
{
	display* screen = (display*)ustc;
	int screenWidth = screen -> b.cols;
	int screenHeight = screen -> b.rows;

	if(event == CV_EVENT_LBUTTONDOWN)
	{
		screen -> lpressed = true;
		screen -> tmpx = x;
		screen -> tmpy = y;
	}
	else if(event == CV_EVENT_LBUTTONUP && flags == FITSMARKER_CTRL)
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
	else if(event == CV_EVENT_LBUTTONUP && flags == FITSMARKER_SHIFT)
	{
		if(screen -> lpressed)
		{
			std::cout << "Set ROI, eliminate all edge inside ROI" << std::endl;
			if(x < screen -> tmpx)
			{
				std::swap(x, screen -> tmpx);
			}
			if(y < screen -> tmpy)
			{
				std::swap(y, screen -> tmpy);
			}
			screen -> eliminateEdge(screen->tmpx, x, screen->tmpy, y);
			screen -> lpressed = false;
			screen -> reframe();
		}
	}
	else if(event == CV_EVENT_LBUTTONUP)
	{
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
				screen -> larger.setx(x, screenWidth);
				screen -> larger.sety(y, screenHeight);
				screen -> unmarkLarger.setx(x, screenWidth);
				screen -> unmarkLarger.sety(y, screenHeight);
				screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
				screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
				screen -> edgeMapTmp = newEdgeMap;
				screen -> reframe();
			}
		}
	}
	else if(event == CV_EVENT_MOUSEMOVE)
	{
		screen -> larger.setx(x, screenWidth);
		screen -> larger.sety(y, screenHeight);
		screen -> unmarkLarger.setx(x, screenWidth);
		screen -> unmarkLarger.sety(y, screenHeight);
		screen -> larger.refresh(screen -> b, screen -> g, screen -> r);
		screen -> unmarkLarger.refresh(screen -> reimage, screen -> reimage, screen -> reimage);
		screen -> reframe();
	}
}

