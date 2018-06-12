## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

'''
This file includes the implementation of Logistic Regression to solve binary classification
with tensorflow
'''

import numpy as np
import tensorflow as tf
import json
import os

class LRModel:

    def __init__(self):
        self.loaded = False
        self.phase = -1

    def getBias(self, name):
        res = tf.truncated_normal(shape=[1], stddev = .5)
        return tf.Variable(res, name = name)

    def getWeight(self, shape, name):
        res = tf.truncated_normal(shape=shape, stddev = .5)
        return tf.Variable(res, name = name)

    def buildModel(self):
        X = tf.placeholder(tf.float32, [None, self.featureLength])
        Y = tf.placeholder(tf.float32, [None])

        self.X = X
        self.Y = Y

        W = self.getWeight([self.featureLength, 1], name = 'weight')
        bias = self.getBias(name = 'bias')
        self.W = W
        self.bias = bias

        self.production = tf.add(tf.matmul(self.X, self.W), self.bias)
        self.pred = tf.sigmoid(self.production)

        if self.phase == 0:
            self.loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(labels=self.Y, logits=self.production[:,0]))
            self.optimizer = tf.train.GradientDescentOptimizer(self.learningRate).minimize(self.loss)
        return

    def saveParams(self, tgtDir):
        modelFile = os.path.join(tgtDir, 'model.npy')
        np.save(modelFile, self.paramList)
        return

    def loadTrainConfig(self, configFile):
        config = json.load(open(configFile, 'r'))
        self.batchsize = int(config['batchsize'])
        self.batches = int(config['batches'])
        self.featureLength = int(config['featurelength'])
        self.learningRate = float(config['learningrate'])
        self.phase = 0

    def train(self, tgtDir, configFile, input_fn):
        self.loadTrainConfig(configFile)
        self.buildModel()

        init = tf.global_variables_initializer()
        with tf.Session() as sess:
            sess.run(init)
            for i in range(self.batches):
                x, y = input_fn()
                sess.run(self.optimizer, feed_dict={self.X:x, self.Y:y})
                loss = sess.run(self.loss, feed_dict={self.X:x, self.Y:y})
                pred = sess.run(self.pred, feed_dict={self.X:x})
                print "Batch #" + str(i) + " Loss = " + str(loss)

                if i % 50 == 0:
                    print 'saveing...weights'
                    resw = sess.run(self.W)
                    resb = sess.run(self.bias)
                    self.paramList = [resw, resb]
                    self.saveParams(tgtDir)
            resw = sess.run(self.W)
            resb = sess.run(self.bias)
            self.paramList = [resw, resb]
        self.saveParams(tgtDir)

    def loadWeights(self, modelFile):
        self.paramList = np.load(modelFile)
        self.loadW = tf.assign(self.W, self.paramList[0])
        self.loadBias = tf.assign(self.bias, self.paramList[1])
        return

    def predict(self, x):
        assert(self.loaded == True)
        init = tf.global_variables_initializer()
        with tf.Session() as sess:
            sess.run(init)
            sess.run([self.loadW, self.loadBias])
            predict = sess.run(self.pred, feed_dict={self.X:x})
            return predict

    def loadExistedModel(self, configFile, modelFile):
        config = json.load(open(configFile, 'r'))
        self.featureLength = int(config['featurelength'])
        self.buildModel()
        self.loadWeights(modelFile)
        self.loaded = True
        self.phase = 1

