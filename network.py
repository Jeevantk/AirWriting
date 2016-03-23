import numpy as np
import cv2 

def sigmoid(z):
    
    return 1.0/(1.0+np.exp(-z))

class Network(object):

    def __init__(self,sizes):
        self.num_layers = 5
        self.sizes = [784,50,80,30,10]
        self.biases =np.load('biases.npy')
        self.weights = np.load('weights.npy')

    def feedforward(self, a):
        
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        print(a)

    def evaluate(self):
        k=0.00392156862
        img=cv2.imread("test.jpg",0)
        a = np.array(img)
        a=np.reshape(a,(784,1))
        a=k*a

       
        for b, w in zip(self.biases,self.weights):
            a = sigmoid(np.dot(w, a)+b)
        k=np.argmax(a)
        f = open("data2.txt", "w")
        f.write(str(k))
        f.close()
	##print(a)

