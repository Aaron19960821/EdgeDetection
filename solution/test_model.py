## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import tensorflow as tf
import numpy as np
import random as rd
import models.lr as lr
import matplotlib.pyplot as plt

xFile = './data/logistic_x.in.txt'
yFile = './data/logistic_y.in.txt'

x = np.loadtxt(xFile)
y = np.loadtxt(yFile)

def input():
    resx = np.zeros([80,2], dtype=np.float32)
    resy = np.zeros([80], dtype=np.float32)

    xx = rd.randint(0, len(x)-1)
    
    for i in range(80):
        index = (xx+i)%len(x)
        resx[i] = x[index]
        resy[i] = y[index]
        if resy[i] < 0:
            resy[i] = 0.0

    return resx, resy

def main():
    net = lr.LRModel()
    net.train("./temp", "./temp/build.json", input)
    net1 = lr.LRModel()
    net1.loadExistedModel('./temp/build.json','./temp/model.npy')

    #print res
    type1x = []
    type1y = []
    type2x = []
    type2y = []
    for i in range(len(x)):
        resx = np.zeros([1,2], dtype=np.float32)
        resx[0] = x[i]
        res = net1.predict(resx)

        if res[0] <= 0.5:
            type1x.append(x[i][0])
            type1y.append(x[i][1])
        else:
            type2x.append(x[i][0])
            type2y.append(x[i][1])

    xx = np.arange(-1, 8)
    yy = -(0.6/1.13)*xx + 2.06
    plt.plot(type1x, type1y, 'ro')
    plt.plot(type2x, type2y, 'bo')
    plt.plot(xx, yy)
    plt.show()

main()
    
