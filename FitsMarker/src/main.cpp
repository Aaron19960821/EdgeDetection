/*************************************************************************
    > File Name: main.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 20:42:04 2018
 ************************************************************************/

#include<iostream>
#include<opencv2/highgui.hpp>
#include<utility>
#include<assert.h>
#include<string.h>

#include"fitsutils.h"
#include"imageutils.h"
#include"cannydetector.h"
#include"display.h"
using namespace std;

void printHelp()
{
	cout << "FitsMarker " << "-d [filename]" << "Run Canny Detector from a list of images." << endl;
	cout << "FitsMarker " << "-p [filename]" << "Show image with edges" << endl;
	return 0;
}

int main(int argc, char** argv)
{
	assert(argc > 2);
	if(strcmp(argv[1], "-d") == 0)
	{
		cannyDetector detector(120, 120.0*3);
		detector.detectFromBatch(argv[2]);
	}
	else if(strcmp(argv[1], "-p") == 0)
	{
		display screen(argv[2]);
	}
	else
	{
		printHelp();
	}
	return 0;
}

