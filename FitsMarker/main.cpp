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
#include<cstdlib>

#include"src/fitsutils.h"
#include"src/imageutils.h"
#include"src/cannydetector.h"
#include"src/display.h"
using namespace std;

void printHelp()
{
	cout << "FitsMarker " << "-d [filename]" << "Run Canny Detector from a list of images." << endl;
	cout << "FitsMarker " << "-p [filename]" << "Show image with edges" << endl;
	return;
}

int main(int argc, char** argv)
{
	assert(argc > 2);
	if(strcmp(argv[1], "-d") == 0)
	{
		double thresh1 = 120.0;
		double thresh2 = 120.0*2;
		if(argc >= 5)
		{
			thresh1 = atof(argv[3]);
			thresh2 = atof(argv[4]);
		}
		cannyDetector detector(120, 120.0*3);
		detector.detectFromBatch(argv[2]);
	}
	else if(strcmp(argv[1], "-p") == 0)
	{
		display screen(argv[2]);
		for(int i=0; i<5; i++)
		{
			char c;
			cout << "Save the annotation or not?[y/n]" << endl;
			cin >> c;
			if(c == 'y')
			{
				screen.saveAnnotation();
			}
			else if(c == 'n')
			{
				break;
			}
		}
	}
	else
	{
		printHelp();
	}
	return 0;
}

