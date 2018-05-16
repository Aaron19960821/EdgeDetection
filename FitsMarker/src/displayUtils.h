/*************************************************************************
    > File Name: displayUtils.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Tue May 15 21:25:48 2018
 ************************************************************************/

#ifndef DISPLAYUTILS_H
#define DISPLAYUTILS_H

#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

namespace cv
{
	void imgOnMouse(int event, int x, int y, int flags, void* ustc);
}

#endif
