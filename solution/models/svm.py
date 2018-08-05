## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

'''
This file includes the implementation of linear svm to 
solve binary classification problems with Tensorflow
'''

import numpy as np
import tensorflow as tf
import json
import os

class SVMModel:

    def __init__(self):
        self.loaded = False
        self.phase = -1

    def train(self, tgtDir, configFile, input_fn):
        self.loadTrainConfig()
        self.buildModel()

