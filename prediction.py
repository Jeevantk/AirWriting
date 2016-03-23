import numpy as np
import matplotlib.pyplot as plt
caffe_root = '../caffe/'
import sys
sys.path.insert(0, caffe_root + 'python')
import caffe
import os


if not os.path.isfile('lenet_2_iter_10000.caffemodel'):
	print('Wrong Location of File')

caffe.set_mode_cpu() 

net = caffe.Net('lenet.prototxt','lenet_2_iter_10000.caffemodel',caffe.TEST)


