# AirWriting
Hand Gesture Recognition
Members:
Jeevan Thomas Koshy
Roll No: ME14B030
E-mail: jeevan.thomaskoshy@gmail.com
Phone No: +919790469245
Johaan Chacko Mathew
Roll No: ME14B031
E-mail: johaanchackomathew@gmail.com
Phone No: +919790469591
Project Code:
https://github.com/Jeevantk/AirWriting
Problem Statement:
To decode hand gestures made on air and to use them as an input device.
Abstract:
The Project aimed at providing Human Computer Interface using Hand 
Gestures with the help of a RGBD camera. As a part of this we created a 
program which can recognize the numbers drawn on air.
Summary of Implementation:
The initial problem we had to solve was to detect the hand accurately in a 
video frame. This is an unsolved research problem with a single camera. 
We tried out many approaches based on color, background subtraction etc.
for this. We were unable to detect the hand effectively in all background 
using a single camera. In our experiments we found a better method for 
color based search. We will be describing the method below.
In Order to make a solution which works in all backgrounds, we decided on 
relying on a depth camera (Microsoft Kinect) for detecting the hand 
properly. The fingertip was tracked and was used as a pen to draw a 
particular number on air. In order to automate the beginning and ending of 
a gesture, we trained a Neural network for finding if the hand is in writing 
mode or not. A detailed implementation procedure will be given below. After
drawing the output was given to a Neural Network for predicting the drawn 
number.
Detailed Implementation Procedure:
1.Hand Tracking:
Initial approach for detecting hand was based on features like color, 
Background Subtraction etc. These approaches cannot be generalized for 
all conditions. 
But we were able to arrive at a new method based on color 
based searching
. We will be discussing about that method at the end of this
paper. As far as the project was concerned we used a Kinect for obtaining 
the depth of the image. The depth along with color based filters detected 
the hand very well. We also tried various other methods including FEMD for
recognizing various simple gestures.
2.Defining a Writing position:
The first problem was to define a writing position so that the program can 
identify when to start drawing based on the tip of the hand. We used a 
binary classifying neural network for this purpose. I actually trained two 
neural networks, one of which (a fully connected neural network) was 
written by myself without the use of any libraries and one which was trained
using 
Caffe
 (a Convolutional Neural Network). Both of the above networks 
were trained using by a dataset that I manually created which contained 
around 700 positive samples and 2000 negative samples. They gave 
accuracies of 91 % and 94% respectively on a test dataset which was not 
included for training these networks. I defined the writing position as this.
Figure 1
Figure 2
The program will use the tip of the hand as a pen and draw it into an image.
When we withdraw the hand from the writing position (like in fig 2) we will 
stop this drawing and give the output to the neural network described in the
next method for recognizing the drawn number.
3.Recognizing the given Input hand drawn number: 
The problem in this section is to recognize handwritten numbers. For this 
purpose, I trained two Neural Networks for classifying the drawn image into
10 classes. The first one (a fully connected neural network  of shape 
(784,784,80,30,10))was developed from the ground up and the second one
was trained using 
Caffe
 (a Convolutional Neural Network).I used the 
MNIST
 dataset for training this network. They gave accuracies of 97 % and
99% respectively on a test dataset which was not included for training 
these networks.
Some sample Input which the trained network predicts correctly
4.Initialise drawing in the program:
In order to initialize the program to start checking for numbers, a 
combination of swipes has to be performed. The program will enter into 
writing mode on performing a horizontal swipe from left to right followed by 
a vertical swipe from top to bottom. The program will leave from writing 
mode if a similar gesture is performed again.
Implementation:
All the above mentioned 4 steps was run on 4 parallel threads (MIMD 
model) to ensure a smooth working of the program. OpenCV was used as 
the Computer Vision Library and Caffe was used for the neural networks. 
Libfreenect was also used for getting the depth image from the Kinect. No 
other libraries written for Kinect were used in the project
A side Effect of the Project
I was able to develop a better method for color based segregation of an 
object. To the best of my Knowledge I haven’t found this method elsewhere
and I believe that this is the first time anyone has tried this method. I shall 
be writing about this method in a different paper.
Note:
This project was exhibited at Centre For Innovation, (CFI) IIT Madras Open
House and was a huge success there. The project also won the 
Most 
Technically advanced Project Award
 in Center for Innovation, (CFI) IIT 
Madras 
for the year 2015-2016.
A link to the color based segregation is 
here
