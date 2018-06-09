## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

"""
This file contains some functions for natural image processing
"""

from astropy.io import fits as fits
from astropy.table import Table as table
import numpy as np
import cv2

def gaussianBlur(im, sigma, ksize = 3):
    """
    Compute gaussan blur
    im: input image
    sigma: variance for gaussian function
    """
    return cv2.GaussianBlur(im, ksize = (ksize, ksize), sigmaX=sigma, sigmaY=sigma)

def differenceOfGaussian(im, sigma1, sigma2, ksize = 3):
    """
    Compute DoG
    im: input image
    sigma1: variance for the first Gaussian filter
    sigma2: variance for the second Gaussian filter
    """
    im1 = gaussianBlur(im, sigma1, ksize)
    im2 = gaussianBlur(im, sigma2, ksize)
    return im1 - im2

def sobelx(im, ksize):
    """
    Compute Sobel of an image
    im: input image
    ksize: the size of a kernel
    """
    return cv2.Sobel(im, ddepth = -1, ksize = ksize, dx = 1, dy = 0)

def sobely(im, ksize):
    """
    Compute Sobel of an image in y
    im: input image
    ksize: the size of a kernel
    """
    return cv2.Sobel(im, ddepth = -1, ksize = ksize, dx = 0, dy = 1)

def magnitude(im, ksize):
    """
    Compute magnitude of an image
    im: input image
    ksize = the size of a kernel
    """
    dxMat = sobelx(im, ksize)
    dxMat = sobely(im, ksize)
    mag, angle = cv2.cartToPolar(dxMat, dyMat)
    return mag

def angle(im, ksize):
    """
    Compute the orientation of an image
    im: input image
    ksize: the size of a kernel
    """
    dxMat = sobelx(im, ksize)
    dxMat = sobely(im, ksize)
    mag, angle = cv2.cartToPolar(dxMat, dyMat)
    return angle

def crop(im, x, y, w, h, padding = 'same'):
    maxh = len(im)
    maxw = len(im[0])

    l = x - w
    d = y - h

    res = np.zeros([maxh, maxw], dtype = im.dtype)
    for i in range(d, d+2*h+1, 1):
        for j in range(l, l+2*w+1, 1):
            if padding == 'zero':
                if i < 0 or j < 0 or i >= maxh or j >= maxw:
                    continue
                else:
                    res[i][j] = im[i][j]
            elif padding == 'same':
                actuali = i
                actualj = j
                if i < 0:
                    actuali = 0
                elif i >= maxh:
                    actuali = maxh - 1
                elif actualj < 0:
                    actualj = 0
                elif actualj >= maxw:
                    actualj = maxw - 1
                res[i][j] = im[i][j]
    return res

def mat2vector(mat):
    res = np.zeros(mat.size, dtype = mat.dtype)
    for i in range(len(mat)):
        for j in range(len(mat[i])):
            res[i*len(mat[i])+j] = mat[i][j]
    return mat


