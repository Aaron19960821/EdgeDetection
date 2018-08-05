## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

import numpy as np
import xgboost as xgb
import json
import os

class xgboostTree:

    def __init__(self, configFile, phase):
        with open(configFile, 'r') as f:
            self.config = json.load(f)
        #self.learningrate = self.config['learningrate']
        self.booster = self.config['booster']
        self.nthread = self.config['nthread']
        self.eta = self.config['eta']
        self.gamma = self.config['gamma']
        self.max_depth = self.config['max_depth']
        self.subsample = self.config['subsample']
        self.min_child_weight = self.config['min_child_weight']
        self.max_leaves = self.config['max_leaves']
        self.batches = self.config['batches']
        self.objective = self.config['objective']

        if phase == 1:
           param = {
                'max_depth': self.max_depth,
                'max_leaves': self.max_leaves,
                'nthread': self.nthread,
                'booster': self.booster,
                'eta': self.eta,
                'gamma': self.gamma,
                'subssample': self.subsample,
                'objective': self.objective
                }
           self.model = xgb.Booster(param)
           self.model.load_model(os.path.dirname(configFile)+'/'+self.config['model_file'])


    def saveConfig(self, tgtDir):
        config = self.config
        config['model_file'] = 'model.bst'
        with open(os.path.abspath(tgtDir) + '/model.json', 'w') as f:
            json.dump(config, f)
        return

    def train(self, tgtDir, input_fn):
        X, Y = input_fn()
        print len(X)
        dataMatrix = xgb.DMatrix(data=X, label=Y)
        param = {
                'max_depth': self.max_depth,
                'max_leaves': self.max_leaves,
                'nthread': self.nthread,
                'booster': self.booster,
                'eta': self.eta,
                'gamma': self.gamma,
                'subssample': self.subsample,
                'objective': self.objective
                }
        bst = xgb.train(param, dataMatrix, self.batches)
        bst.save_model(os.path.abspath(tgtDir) + '/model.bst')
        self.saveConfig(tgtDir)
        print "Train Finished!!"

    def predict(self, input_fn):
        X = input_fn()
        dataMatrix =xgb.DMatrix(data=X)
        return self.model.predict(dataMatrix)


