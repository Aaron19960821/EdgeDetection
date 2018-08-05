## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import tensorflow as tf
import numpy as np
import utils
import cv2
import json
import time
import os

from utils import *


class segnet:

    def __init__(self, configFile):
        with open(configFile, 'r') as f:
            self.config = json.load(f)
            self.width = self.config['width']
            self.height = self.config['height']
            self.channel = self.config['channel']
            self.learningrate = self.config['learningrate']
            self.momentum = self.config['momentum']
            self.batchsize = self.config['batchsize']
            self.batchnum = self.config['batchnum']
            self.classes = self.config['classes']

    def buildNet(self):
        #TODO: Implemente this method
        self.X = tf.placeholder(dtype=tf.float32, shape=(self.batchsize, self.width, self.height, self.channel))
        self.Y = tf.placeholder(dtype=tf.int32, shape=(self.batchsize, self.width, self.height))

        norm = tf.nn.lrn(self.X, depth_radius=5, bias=1.0, alpha=1e-4, beta=0.75)
        # Encoder of segnet
        self.enconv1 = batchnorm(conv2d(norm, [3,3,self.channel,64], [1,1,1,1]))
        self.enconv2 = batchnorm(conv2d(self.enconv1, [3,3,64,64], [1,1,1,1]))
        self.enpool1 = maxpooling2d(self.enconv2, [1,2,2,1], [1,2,2,1])

        self.enconv3 = batchnorm(conv2d(self.enpool1, [3,3,64,128], [1,1,1,1]))
        self.enconv4 = batchnorm(conv2d(self.enconv3, [3,3,128,128], [1,1,1,1]))
        self.enpool2 = maxpooling2d(self.enconv4, [1,2,2,1], [1,2,2,1])

        self.enconv5 = batchnorm(conv2d(self.enpool2, [3,3,128,256], [1,1,1,1]))
        self.enconv6 = batchnorm(conv2d(self.enconv5, [3,3,256,256], [1,1,1,1]))
        self.enpool3 = maxpooling2d(self.enconv6, [1,2,2,1], [1,2,2,1])

        self.enconv7 = batchnorm(conv2d(self.enpool3, [3,3,256,512], [1,1,1,1]))
        self.enconv8 = batchnorm(conv2d(self.enconv7, [3,3,512,512], [1,1,1,1]))
        self.enpool4 = maxpooling2d(self.enconv8, [1,2,2,1], [1,2,2,1])

        self.enconv9 = batchnorm(conv2d(self.enpool4, [3,3,512,512], [1,1,1,1]))
        self.enconv10 = batchnorm(conv2d(self.enconv9, [3,3,512,512], [1,1,1,1]))
        self.enpool5 = maxpooling2d(self.enconv10, [1,2,2,1], [1,2,2,1])

        # Decoder of segnet
        self.depool1 = deconv2d(self.enpool5, [3,3,512,512], self.enconv10.shape, [1,1,1,1])
        self.deconv1 = batchnorm(conv2d(self.depool1, [3,3,512,512], [1,1,1,1]))
        self.deconv2 = batchnorm(conv2d(self.deconv1, [3,3,512,512], [1,1,1,1]))

        self.depool2 = deconv2d(self.deconv2, [3,3,512,512], self.enconv8.shape, [1,1,1,1])
        self.deconv3 = batchnorm(conv2d(self.depool2, [3,3,512,256], [1,1,1,1]))
        self.deconv4 = batchnorm(conv2d(self.deconv3, [3,3,256,256], [1,1,1,1]))

        self.depool3 = deconv2d(self.deconv4, [3,3,256,256], self.enconv6.shape, [1,1,1,1])
        self.deconv5 = batchnorm(conv2d(self.depool3, [3,3,256,128], [1,1,1,1]))
        self.deconv6 = batchnorm(conv2d(self.deconv5, [3,3,128,128], [1,1,1,1]))

        self.depool4 = deconv2d(self.deconv6, [3,3,128,128], self.enconv4.shape, [1,1,1,1])
        self.deconv7 = batchnorm(conv2d(self.depool4, [3,3,128,64], [1,1,1,1]))
        self.deconv8 = batchnorm(conv2d(self.deconv7, [3,3,64,64], [1,1,1,1]))

        self.depool5 = deconv2d(self.deconv8, [3,3,64,64], self.enconv2.shape, [1,1,1,1])
        self.deconv9 = batchnorm(conv2d(self.depool5, [3,3,64,32], [1,1,1,1]))
        self.deconv10 = batchnorm(conv2d(self.deconv9, [3,3,32,self.classes], [1,1,1,1]))

        self.pred = tf.nn.softmax(self.deconv10)
        self.oneHotY = tf.one_hot(self.Y, depth=2, on_value=1.0, off_value=0.0)
        self.loss = tf.losses.softmax_cross_entropy(onehot_labels=self.oneHotY, logits=self.pred)
        print self.loss.shape
        self.optimizer = tf.train.AdamOptimizer(self.learningrate).minimize(self.loss)


    def saveConfig(tgtDir):
        with open(os.path.abspath(tgtDir)+'model.json', 'r') as f:
            json.dump(self.config, f)
        return

    def train(self, trainfile, tgtDir, inputfn):
        self.buildNet()
        init = tf.global_variables_initializer()
        saver = tf.train.Saver()

        with tf.Session() as sess:
            sess.run(init)
            #TODO: implement the process of train
            for i in range(self.batchsize):
                startTime = time.time()
                x, y = inputfn(trainfile, self.batchsize)

                #sess.run(self.optimizer, feed_dict={
                #    self.X: x,
                 #   self.Y: y
                  #  })
                curLoss = sess.run(self.loss, feed_dict={
                    self.X: x,
                    self.Y: y
                    })
                endTime = time.time()
                print("Batch #%d processing time %.2fs, loss = %.5f"%(i+1, endTime-startTime, curLoss))

                if (i+1)%50 == 0:
                    saver.save(sess, os.path.abspath(tgtDir)+'model.ckpt')
                    print "Model Saved.."
            self.saveAll(tgtDir)
            saver.save(sess, os.path.abspath(tgtDir)+'model.ckpt')
            print 'SegNet Train Finished!!'
            return
