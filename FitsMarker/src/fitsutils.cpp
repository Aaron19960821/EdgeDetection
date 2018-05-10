/*************************************************************************
    > File Name: fitsutils.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Wed May  9 19:51:44 2018
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<fitsio.h>
#include<opencv2/highgui.hpp>

cv::Mat readFits(char* filename, int mode)
{
	fitsfile* fptr;
	int status = 0;
	int anynull;

	if(fits_open_file(&fptr, filename, mode, &status))
	{
		std::cout << "Can not find the file " << filename << std::endl;
		return cv::Mat();
	}

	long naxis[2] = {1, 1};
	long fpixel[2] = {1, 1};
	fits_get_img_size(fptr, 2, naxis, &status);

	float* datatmp = (float*)malloc(naxis[0]*naxis[1]*sizeof(float));
	fits_read_pix(fptr, TFLOAT, fpixel, naxis[0]*naxis[1], 0, datatmp, &anynull, &status);

	cv::Mat data(naxis[0], naxis[1], CV_32F, datatmp);

	free(datatmp);
	fits_close_file(fptr, &status);
	fits_report_error(stderr, status);
	return data;
}

