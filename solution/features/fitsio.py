## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

"""
This file contains APIs that enables users to read and write fits file
"""

from astropy.io import fits as fits
from astropy.table import Table as table
import numpy as np

def readFits(filename):
    """
    read fits from a given path
    filename: the path to a fits file, absolute path encouraged
    """
    hdul = fits.open(filename)
    return hdul[0].data

def writeFits(filename, im):
    """
    write an image to a given path
    im: the image to be written
    filename: the path to be written
    """
    t = table(im, name='data')
    t.write(filename, format='fits')


