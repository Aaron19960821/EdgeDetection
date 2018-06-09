## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import cv2
import numpy as np
import features.imageutils as utils
import features.hdf5 as hdf5

#im = cv2.imread("./example.jpeg")
#gaussian = utils.differenceOfGaussian(im, 2.0, 1.0, 3)
#gaussian = utils.sobely(im, 3)
#gaussian = utils.crop(im[:,:,0:1], 50, 50, 40, 40)

#print len(im)
#print len(im[0])

#vector = utils.mat2vector(gaussian[:,:,0:1])
#print vector.size

def testhdf5():
    hdf5.createhdf5("./hello.hdf5", 2, 1)
    f = hdf5.openhdf5('./hello.hdf5')
    print f.keys
    hdf5.insert(f, np.array([1,1]), np.array([0]))
    hdf5.insert(f, [1,1], [0])
    hdf5.insert(f, [1,1], [0])
    hdf5.insert(f, [1,1], [0])
    hdf5.insert(f, [1,1], [0])
    print f['meta'][0]
    hdf5.delete(f, 0)
    hdf5.delete(f, 0)
    hdf5.delete(f, 0)
    hdf5.delete(f, 0)
    print f['meta'][1]
    hdf5.closehdf5(f)

testhdf5()
