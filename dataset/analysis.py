#!coding=utf-8

from astropy.io import fits as fits
import numpy as np
import matplotlib.pyplot as plt
import os
import sys

def openImage(filepath):
    hdul = fits.open(filepath)
    return hdul[0].data


def analysisColorDistribution(image):
    maxPixel = -1
    for row in image:
        for pixel in row:
            if maxPixel < pixel:
                maxPixel = pixel

    print "With maxpixel " + str(maxPixel)
    x = [i for i in range(int(maxPixel) + 1)]
    y = [0 for i in range(int(maxPixel) + 1)]

    for row in image:
        for pixel in row:
            if pixel > 300.0:
                y[int(pixel)] += 1


    print "ploting..."
    plt.title('Distribution Of Pixel')
    plt.xlabel('Intense')
    plt.ylabel('PixelNumber')
    plt.plot(x, y)
    print "Showing..."
    plt.show()

def main():
    command = sys.argv[1]
    if command == '-a' and len(sys.argv) > 2:
        im = openImage(sys.argv[2])
        analysisColorDistribution(im)

main()

