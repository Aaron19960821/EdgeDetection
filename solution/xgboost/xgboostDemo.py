## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

from model import xgboostTree as tree
import numpy as np
import matplotlib.pyplot as plt

def input_fn():
    x = np.loadtxt('../data/logistic_x.in.txt')
    y = np.loadtxt('../data/logistic_y.in.txt')

    for i in range(len(y)):
        if y[i] < 0.0:
            y[i] = 0.0

    return x,y

def input_pred():
    x = np.loadtxt('../data/logistic_x.in.txt')
    return x

def main():
    model = tree('./build.json', 0)
    model.train('./target/', input_fn)

    net1 = tree('./target/model.json', 1)
    pred = net1.predict(input_pred)
    print pred

    xx = input_pred()
    #print res
    type1x = []
    type1y = []
    type2x = []
    type2y = []
    for i in range(len(xx)):
        if pred[i] < 0.5:
            type1x.append(xx[i][0])
            type1y.append(xx[i][1])
        else:
            type2x.append(xx[i][0])
            type2y.append(xx[i][1])
    plt.plot(type1x, type1y, 'ro')
    plt.plot(type2x, type2y, 'bo')
    #plt.plot(xx, yy)
    plt.show()
    

main()
    
