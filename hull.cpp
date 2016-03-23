#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "stdio.h"
 
using namespace cv;
using namespace std;
double min_face_size=20;
double max_face_size=200;
Mat detectFace(Mat image)
{
 // Load Face cascade (.xml file)
 CascadeClassifier face_cascade( "fist.xml" );
 
 // Detect faces
 std::vector<Rect> faces;
 face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
int z=faces.size();
//printf("%d\n",z);
 
 // Draw circles on the detected faces
 for( int i = 0; i < faces.size(); i++ )
 {
  Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
  ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0,0,0 ), 5, 8, 0 );
 } 
 return image;
}
int main( int argc, char** argv )
{ 
 int largest_contour_index=0;
 Rect bounding_rect;
 int largest_area=0;
 int iLowH=0;
 int iHighH=33;
 int iLowS=63;
 int iHighS=144;
 int iLowV=61;
 int iHighV=255;
 int thresh = 100;
 Mat img,gray,hsv,canny;
 VideoCapture cap(0);
 namedWindow("hsv",CV_WINDOW_AUTOSIZE);
 namedWindow("Thresholded Image",CV_WINDOW_AUTOSIZE);
 createTrackbar("Low Hue","hsv",&iLowH,179);
 createTrackbar("High Hue","hsv",&iHighH,179);
 createTrackbar("Low Saturation","hsv",&iLowS,255);
 createTrackbar("High Saturation","hsv",&iHighS,255);
 createTrackbar("Low V","hsv",&iLowV,255);
 createTrackbar("High V","hsv",&iHighV,255);
 //createTrackbar( "Canny thresh:", "Thresholded Image", &thresh,255);
 
 cap.read(img);
 while(1)
 {
 largest_area=0;
 largest_contour_index=0;
 if(!img.empty())
 {
 cap.read(img);
 rectangle(img,Point(10,10), Point(630,470), Scalar( 0,0,0), +15, 4 );
 img=detectFace(img);
 imshow("Hand",img);
 /*cvtColor( src, src_gray, CV_BGR2GRAY );
 blur( src_gray, src_gray, Size(3,3) ); 
 namedWindow( "Source", CV_WINDOW_AUTOSIZE );*/
 cvtColor(img,gray,CV_BGR2GRAY);
 cvtColor(img,hsv,CV_BGR2HSV);
 Mat imgThresholded;
 inRange(hsv,Scalar(iLowH,iLowS,iLowV),Scalar(iHighH,iHighS,iHighV),imgThresholded);
 
 dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 dilate(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 erode(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 erode(imgThresholded,imgThresholded, Mat(), Point(-1,-1),2,1,3);
 //erode(imgThresholded,imgThresholded,Mat(),Point(-1, -1),2,1,3);
 Canny(imgThresholded,canny,thresh,thresh*2, 3 );
 
 vector<vector<Point> > contours;
 vector<Vec4i> hierarchy;
 
 
 //threshold(imgThresholded,canny,200,255,THRESH_BINARY);
 findContours(canny,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0, 0));
 
 
 vector<vector<Point> >hull( contours.size() );
 for( int i = 0; i < contours.size(); i++ )
 {  convexHull( Mat(contours[i]), hull[i], false ); }
 int z=contours.size();
 RNG rng;
 Mat drawing = Mat::zeros(canny.size(), CV_8UC3 );
 for( int i = 0; i<z; i++ ) // iterate through each contour. 
      {
       double a=contourArea( contours[i],false);  //  Find the area of contour
       if(a>largest_area){
       largest_area=a;
       largest_contour_index=i;                //Store the index of largest contour
       bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
       }
	}
 //printf("%d  %d\n",largest_contour_index,z);
 Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
 drawContours( drawing, contours,largest_contour_index, color, 1, 8, vector<Vec4i>(), 0, Point() );
 drawContours( drawing, hull,largest_contour_index, color, 1, 8, vector<Vec4i>(), 0, Point() );
 /*for( int i = 0; i<z; i++ )	
 {
  Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
  drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
  drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
 }*/
 
 
 namedWindow( "Hull demo", CV_WINDOW_AUTOSIZE );
 imshow( "Hull demo", drawing );
  imshow("hsv",hsv);
 imshow("Thresholded Image",imgThresholded);
  }
 char c=waitKey(10);
 if(c=='q')
 {
 //printf("%d %d",img.rows,img.cols);
 break;
 }
 }

}
