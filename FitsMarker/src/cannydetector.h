/*************************************************************************
    > File Name: cannydetector.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Thu May 10 22:16:35 2018
 ************************************************************************/
#ifndef CANNYDETECTOR_H
#define CANNYDETECTOR_H

#include<iostream>
#include<cstdio>
#include<string>
#include"imageutils.h"

class cannyDetector
{
	public:
		cannyDetector(double thresh1, double thresh2);
		cannyDetector();
		cv::Mat detectFromSingleImage(cv::Mat src);
		void detectFromBatch(char* filename);
	private:
		double thresh1;
		double thresh2;
}

#endif

