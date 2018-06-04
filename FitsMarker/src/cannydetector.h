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
#include<fstream>
#include<vector>
#include<utility>

#include"imageutils.h"

class cannyDetector
{
	public:
		explicit cannyDetector(double thresh1, double thresh2);
		explicit cannyDetector();
		~cannyDetector();
		void detectFromBatch(char* filename);
		void detectFromSingleImage(char* filename);
		static void dumpEdgeToFile(std::vector<std::pair<int,int> >edgeMap, const char* filename);
	private:
		cv::Mat getEdgeFromSingleImage(cv::Mat src);
		double thresh1;
		double thresh2;
};

#endif

