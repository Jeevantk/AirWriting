
//#include "libfreenect.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <fstream>

using namespace cv;
using namespace std;

//bool isRGBDepth = false, isDynHandSeg = false, isDots = false;
Scalar white = Scalar(255, 255, 255);
bool die=false;


int main(int argc, char **argv)
{


	// The next two lines must be changed as Freenect::Freenect
	// isn't a template but the method createDevice:
	// Freenect::Freenect<MyFreenectDevice> freenect;
	// MyFreenectDevice& device = freenect.createDevice(0);
	// by these two lines:
	VideoCapture cap(0);
	Mat rgbMat,gray,hsv;
	cap.read(img);

	int iclosep=320;
	int jclosep=240;

	while (!die)
	{
		Mat handSegmented = Mat::zeros(rgbMat.size(), CV_8UC1);
		cap.read(img);
		cvtColor(img,gray,CV_BGR2GRAY);
 		cvtColor(img,hsv,CV_BGR2HSV);
 		Mat imgThresholded;
 		inRange(hsv,Scalar(0,63,61),Scalar(33,144,255),imgThresholded);
 		dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 		dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 		dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 		erode(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
	 	erode(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
		Mat canny

		//namedWindow("HandSegment");
		namedWindow("Image Being Written");

		if(true)
		{

			Mat hsv, mask;
			Mat hsvMask1 = Mat::zeros(rgbMat.size(), CV_8UC1);
			Mat hsvMask2 = Mat::zeros(rgbMat.size(), CV_8UC1);
			cvtColor(rgbMat, hsv, CV_RGB2HSV);
			inRange(hsv, Scalar(0, 0, 0), Scalar(30, 255, 255), hsvMask1);
			inRange(hsv, Scalar(150, 0, 0), Scalar(180, 255, 255), hsvMask2);
			add(hsvMask1, hsvMask2, mask);
			int close=255, iclose=0, jclose=0;

			for(int i=0; i<480; i++)
			{
				for(int j=0; j<640; j++)
				{
					uchar value = mask.at<uchar>(i,j);
					uchar intensity = depthf.at<uchar>(i,j);
					if(close > intensity)
					{
						close = intensity;
						iclose = i;
						jclose = j;
					}


				}
			}
			for(int i=0; i<480; i++)
			{
				for(int j=0; j<640; j++)
				{
					uchar depth = depthf.at<uchar>(i,j);
					uchar &intensity = handSegmented.at<uchar>(i,j);
					if(depth>=close&& depth<=close+8)
						intensity = 255;
				}
			}
			//imshow("DepthImage",depthf);
			//imshow("HandSegment", handSegmented);

			/*Mat display;
			flip(rgbMat,display,1);
			imshow("RGB Image",display);*/
			if(flag==1)
			{
				if(((iclosep-iclose)<100||(iclose-iclose<100))&&((jclosep-jclose)<100||(jclose-jclose)<100))
				{
					circle(savedImage, Point(jclose,iclose),10,255,CV_FILLED, 8,0);
					iclosep=iclose;
					jclosep=jclose;
				}

				flip(savedImage,findChar, 1);
				imshow("Image Being Written",findChar);

			}
			else
			{
				flip(handSegmented,findChar,1);
				imshow("Image Being Written",findChar);

			}

		}

		char k = waitKey(1);
		if( k == 'q' )
		{
			if(flag==1)
			{
				imwrite("Test1.jpg",findChar);
				for(int a = 0; a < 10; a++)
					dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);

				for(int a = 0; a < 10; a++)
					erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				/*dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);*/
				//erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 100);

				int largest_area = 0;
				int largest_contour_index = 0;
				Mat F = findChar.clone();
				Rect bounding_rect,bounding_rect1;
				flag=0;
				Mat save;
				vector<vector<Point> > contours;
				vector<Vec4i> hierarchy;
				findContours(F,contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
				for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
				{
    				double a=contourArea( contours[i],false); //  Find the area of contour
    				bounding_rect=boundingRect(contours[i]);
    				if(a>largest_area)
    				{
        				largest_area=a;
        				largest_contour_index=i;
        				bounding_rect1=boundingRect(contours[i]);
        			}

    				if ( a < 60.0)
					{

    	   				rectangle(findChar,bounding_rect, Scalar(0) , CV_FILLED , 8 , 0 );

    	   			}
				}

				save=findChar(bounding_rect1);

				//rectangle(findChar, bounding_rect, 255,5, 8,0);
				imwrite("digit.jpg",save);
				imwrite("Testing.jpg",findChar);
				savedImage=Mat::zeros(depthf.size(),CV_8UC1);
				findChar=Mat::zeros(depthf.size(),CV_8UC1);
				system("./code");
			}
			destroyAllWindows();
			break;
		}
		if( k == 's' )
		{
			if(flag==0)
				flag=1;
			else if(flag==1)
			{
				imwrite("Test1.jpg",findChar);
				for(int a = 0; a < 10; a++)
					dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);

				for(int a = 0; a < 10; a++)
					erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				/*dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				dilate(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);
				erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 1);*/
				//erode(findChar,findChar, Mat(), Point(-1, -1), 2, 1, 100);

				int largest_area = 0;
				int largest_contour_index = 0;
				Mat F = findChar.clone();
				Rect bounding_rect,bounding_rect1;
				flag=0;
				Mat save;
				vector<vector<Point> > contours;
				vector<Vec4i> hierarchy;
				findContours(F,contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
				for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
				{
    				double a=contourArea( contours[i],false); //  Find the area of contour
    				bounding_rect=boundingRect(contours[i]);
    				if(a>largest_area)
    				{
        				largest_area=a;
        				largest_contour_index=i;
        				bounding_rect1=boundingRect(contours[i]);
        			}

    				if ( a < 60.0)
					{

    	   				rectangle(findChar,bounding_rect, Scalar(0) , CV_FILLED , 8 , 0 );

    	   			}
				}

				save=findChar(bounding_rect1);

				//rectangle(findChar, bounding_rect, 255,5, 8,0);
				imwrite("digit.jpg",save);
				imwrite("Testing.jpg",findChar);
				savedImage=Mat::zeros(depthf.size(),CV_8UC1);
				findChar=Mat::zeros(depthf.size(),CV_8UC1);
				system("./code");


			}
		}

	}

	device.stopVideo();
	device.stopDepth();
	return 0;
}

/*src=Mat::zeros(final2.x-final1.x,final2.x-final1.x,CV_8UC1);
		test=img(Rect(final1.x,final1.y,(final2.x-final1.x),(final2.y-final1.y)));
		test.copyTo(src(0,0,final2.x-final1.x,final2.y-final1.y));
*/
