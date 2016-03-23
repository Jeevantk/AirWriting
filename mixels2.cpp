#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat src=imread(argv[1],0);
	int hist[256]={0};
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			uchar intensity=gray.at<uchar>(i,j);
			hist[intensity]++;	
		}
	}
	int total=src.rows*src.cols;
	float sum=0;
	for(int i=0;i<256;i++)
	{
		sum=sum+i*hist[i];
	}
	float sumB=0;
	int wB=0;
	int wF=0;
	float varMax=0;
	int threshold=0;
	for(int i=0;i<256;i++)
	{
		wB=wB+hist[i];
		if(wB==0)continue;
		wF=total-wB;
		if(wF==0)break;
		sumB=sumB+(float)(i*hist[i]);
		float mB=sumB/wB;
		float mF = (sum - sumB) / wF;
		float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);
		if (varBetween > varMax)
		{
			varMax = varBetween;
      		threshold = i;
		}
   	}
   	for(int i=0;i<src.rows;i++)
   	{
   		for(int j=0;j<src.cols;j++)
   		{
   			uchar &t=gray.at<uchar>(i,j);
   			if(t>=threshold)
   			{
   				t=255;
   			}
   			else
   			{
   				t=0;
   			}
   		}
   	}
   	
}