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

#define FITSMARKER_CTRL 9
#define FITSMARKER_SHIFT 17
#define FITSMARKER_LEFT 2
#define FITSMARKER_RIGHT 3
#define FITSMARKER_UP 0
#define FITSMARKER_DOWN 1
#define FITSMARKER_ESC 27
#define FITSMARKER_ENTER 13

namespace cv
{
	void imgOnMouse(int event, int x, int y, int flags, void* ustc);
	int imgOnKeyboard(int flags, void* ustc);
}

#endif
