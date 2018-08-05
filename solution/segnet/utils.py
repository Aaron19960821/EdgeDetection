## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

def conv2d(inTensor, kernel, strides):
    w = tf.Variable(tf.truncated_normal(shape=kernel, stddev=0.5, dtype=inTensor.dtype))
    b = tf.Variable(tf.truncated_normal(shape=[kernel[3]], stddev=0.2, dtype=inTensor.dtype))
    tmplayer = tf.nn.conv2d(inTensor, w, strides, padding='SAME')
    layer = tf.nn.bias_add(tmplayer, b)
    return tf.nn.relu(layer)

def batchnorm(inTensor):
    mean, variance = tf.nn.moments(inTensor, [0, 1, 2])
    layer = tf.nn.batch_normalization(inTensor, mean, variance, 0.0, 1.0, 1e-3)
    return layer

def maxpooling2d(inTensor, kernel, strides):
    return tf.nn.max_pool(inTensor, kernel, strides, padding='SAME')

def deconv2d(inTensor, kernel, outshape, strides):
    w = tf.Variable(tf.truncated_normal(shape=kernel, stddev=0.5, dtype=inTensor.dtype))
    b = tf.Variable(tf.truncated_normal(shape=[kernel[3]], stddev=0.2, dtype=inTensor.dtype))
    tmplayer = tf.nn.conv2d_transpose(inTensor, w, outshape, strides, padding='SAME')
    layer = tf.nn.bias_add(tmplayer, b)
    return tf.nn.relu(layer)


