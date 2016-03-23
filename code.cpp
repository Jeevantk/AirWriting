#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
using namespace cv;
using namespace std;
struct point {
	int x;
	int y;
};//frame(Rect(174,54,316,376))
point point1;
point point2;
point point3;
point point4;
point final1;
point final2;
int main()
{
	Mat img=imread("digit.jpg",0);
	int flag=0;
	for(int i=0;i<img.rows;i++)
	{
		for(int j=0;j<img.cols;j++)
		{
			uchar t=img.at<uchar>(i,j);
			if(t>0)
			{
				point1.x=j;
				point1.y=i;
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			break;
		}
	}
	flag=0;
	
	for(int j=img.cols-1;j>=0;j--)
	{
		for(int i=0;i<img.rows;i++)
		{
			uchar t=img.at<uchar>(i,j);
			if(t>0)
			{
				point2.x=j;
				point2.y=i;
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			break;
		}
	}
	
	flag=0;
	for(int i=img.rows-1;i>=0;i--)
	{
		for(int j=img.cols-1;j>=0;j--)
		{
			uchar t=img.at<uchar>(i,j);
			if(t>0)
			{
				point3.x=j;
				point3.y=i;
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			break;
		}
	}
	
	flag=0;
	for(int j=0;j<img.cols;j++)
	{
		for(int i=img.rows-1;i>=0;i--)
		{
			uchar t=img.at<uchar>(i,j);
			if(t>0)
			{
				point4.x=j;
				point4.y=i;
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			break;
		}
	}
	
	final1.y=point1.y;
	final1.x=point4.x;
	final2.x=point2.x;
	final2.y=point3.y;
	flag=0;
	
	if((final2.y-final1.y)>=(final2.x-final1.x))
	{
		flag=1;
	}
	Mat src;
	Mat test;

	if(flag==0)//there is a bug here ,Solve it later
	{
		src=Mat::zeros(final2.x-final1.x,final2.x-final1.x,CV_8UC1);
		test=img(Rect(final1.x,final1.y,(final2.x-final1.x),(final2.y-final1.y)));
		test.copyTo(src(Rect(0,(final2.x-final1.x)/2-(final2.y-final1.y)/2,final2.x-final1.x,final2.y-final1.y)));
	}
	if(flag==1)
	{
		src=Mat::zeros(final2.y-final1.y,final2.y-final1.y,CV_8UC1);
		test=img(Rect(final1.x,final1.y,(final2.x-final1.x),(final2.y-final1.y)));
		test.copyTo(src(Rect((final2.y-final1.y)/2-(final2.x-final1.x)/2,0,final2.x-final1.x,final2.y-final1.y)));
	}
	
	/*Mat src;
	src=img(Rect(final1.x,final1.y,final2.x-final1.x,final2.y-final1.y));*/
	//blur(src,src, Size(5,5));
	Size size(22,22);
	Mat dst;
	resize(src,dst,size);
	Mat final=Mat::zeros(28,28,CV_8UC1);
	dst.copyTo(final(Rect(3,3,22,22)));
	blur(final,final,Size(3,3));
	//imshow("testing",final);
	
	imwrite("test.jpg",final);
	system("python run.py");
	//system("lenet_2_iter_10000.caffemodel lenet.prototxt prob test 1 lmdb CPU > data2.txt 2>/dev/null");
	//system("../caffe/build/tools/extract_features_cout_bin lenet_2_iter_10000.caffemodel lenet.prototxt prob test 1 lmdb CPU > data2.txt 2>/dev/null");
	int result;
	ifstream fin;
	fin.open("data2.txt");
	//fscanf("%d", result);
	fin>>result;
	string c;
	ostringstream convert;
	convert << result;
	c = convert.str();
	c=c+".jpg";
	Mat answer=imread(c.c_str());
	imshow("testing",final);
	imshow("Prediction",answer);
	waitKey(0);
	
	
	


}

