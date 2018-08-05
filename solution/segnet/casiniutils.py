## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import tensorflow as tf
import numpy as np
import random as rd
import cv2
from astropy.io import fits as fits

def readFits(filename):
    hdul = fits.open(filename)
    return hdul[0].data

def cropboth(pic, label, index):
    if index == 0:
        return pic[0:512, 0:512], label[0:512, 0:512]
    elif index == 1:
        return pic[512:1024, 0:512], label[512:1024, 0:512]
    elif index == 2:
        return pic[0:512, 512:1024], label[0:512, 512:1024]
    elif index == 3:
        return pic[512:1024, 512:1024], label[512:1024, 512:1024]

def getList(trainfile):
    with open(trainfile, 'r') as f:
        images = []
        labels = []
        for line in f:
            images.append(line.strip().split()[0])
            labels.append(line.strip().split()[1])
        return images, labels

def get_batch(trainfile, batchsize):
    flist, labellist = getList(trainfile)
    num = 0
    image = []
    label = []

    while num < 4:
        index = rd.randint(0, len(labellist)-1)
        pic = readFits(flist[index])
        labtmp = cv2.imread(labellist[index])
        
        if pic.shape[0] == 512:
            im, la = cropboth(pic, labtmp, 0)
            image.append(im)
            label.append(la)
            num += 1
        else:
            for i in range(4-num):
                im, la = cropboth(pic, labtmp, i)
                image.append(im)
                label.append(la)
                print la.shape
            num += 4

    return image, label

