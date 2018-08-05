## This File is created by Yuchen Wong
## @Copyright Yuchen Wong 2018

from model import segnet
from casiniutils import *

def main():
    model = segnet('./build.json')
    model.train('train_eval.txt', '../tgtdir/', get_batch)

main()
