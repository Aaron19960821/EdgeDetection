## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

"""
This dataset contains a lot of APIs for users to
read and write hdf5 datasets
"""

import h5py
import numpy as np
import cv2

def createhdf5(filename, featureLength, labelLength, featureType = np.float32):
    '''
    create a new hdf5 file with given feature length and label length
    featureLength - The length of feature vector
    labelLength - The length of label vector
    featureType - The type of feature
    '''
    with h5py.File(filename, 'a') as f:
        f['meta'] = np.array([1,0,featureLength,labelLength])
        dset = f.create_dataset('data', shape=(1, featureLength), maxshape=(None, featureLength), dtype = featureType)
        label = f.create_dataset('label', shape=(1, labelLength), maxshape=(None, labelLength), dtype = np.int32)
        f.close()

def openhdf5(filename):
    '''
    Open a hdf5 file
    '''
    f = h5py.File(filename, 'a')
    return f

def insert(f, newFeature, newLabel):
    '''
    Insert a new line to dataset
    newFeature - new feature vector
    newLabel - new label vector
    '''
    assert(len(newFeature) == f['meta'][2])
    assert(len(newLabel) == f['meta'][3])

    if f['meta'][0] == f['meta'][1]:
        expand(f)
    length = f['meta'][1]
    f['data'][length,:] = newFeature
    f['label'][length,:] = newLabel
    f['meta'][1] += 1
    return

def delete(f, index):
    '''
    delete a line from dataset
    index - the index of data
    '''
    length = f['meta'][1]
    assert(index >= 0 and index < length)

    for i in range(index, length, 1):
        f['data'][i] = f['data'][i + 1]
        f['label'][i] = f['label'][i + 1]

    f['meta'][1] -= 1
    if f['meta'][1] < f['meta'][0] / 4:
        shrink(f)
    return

def shrink(f):
    '''
    Shrink the dataset
    '''
    f['meta'][0] = f['meta'][0] / 2
    f['data'].resize((f['meta'][0], f['meta'][2]))
    f['label'].resize((f['meta'][0], f['meta'][3]))
    return

def expand(f):
    '''
    Expand the dataset
    '''
    f['meta'][0] = f['meta'][0] * 2
    f['data'].resize((f['meta'][0], f['meta'][2]))
    f['label'].resize((f['meta'][0], f['meta'][3]))
    return

def closehdf5(f):
    '''
    Close the hdf5 file
    '''
    f.close()


