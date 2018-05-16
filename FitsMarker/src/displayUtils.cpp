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
	else if(event == CV_EVENT_LBUTTONUP)
	{
		if(screen -> lpressed)
		{
			if(x < screen -> tmpx)
			{
				std::swap(x, screen -> tmpx);
			}
			if(y < screen -> tmpy)
			{
				std::swap(y, screen -> tmpy);
			}
			for(auto pi : screen -> edgeMap)
			{
				if(pi.first >= screen -> tmpx && pi.first <= x && pi.second >= screen -> tmpy && pi.second <= y)
				{
					continue;
				}
				else
				{
					screen -> edgeMapTmp.push_back(pi);
				}
			}
			screen -> lpressed = false;
			screen -> reframe();
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
		for(int i=d; i<=u; i++)
		{
			for(int j=l; j<=r; j++)
			{
				for(int k=(i-d)*10; k<(i-d)*10+10; k++)
				{
					for(int p=(j-l)*10; p<(j-l)*10+10; p++)
					{
						screen -> smallb.at<uchar>(k,p) = screen -> b.at<uchar>(i,j);
						screen -> smallg.at<uchar>(k,p) = screen -> g.at<uchar>(i,j);
						screen -> smallr.at<uchar>(k,p) = screen -> r.at<uchar>(i,j);
						if(i == y && j == x)
						{
							screen -> smallb.at<uchar>(k,p) = 255;
							screen -> smallg.at<uchar>(k,p) = 0;
							screen -> smallr.at<uchar>(k,p) = 0;
						}
					}
				}
			}
		}
		screen -> reframe();
	}
}

