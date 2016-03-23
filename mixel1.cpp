#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat F = findChar.clone();
	Rect bounding_rect,bounding_rect1;
	Mat img=imread(argv[1],0);

	vector<vector<Point> > contours;
 	vector<Vec4i> hierarchy;
 	Mat Binary=Mat::zeros(img.size(),CV_8UC1);
	for(int i=0;i<img.rows;i++)
	{
		for(int j=0;j<img.colsl;j++)
		{
			uchar t=img.at<uchar>(i,j);
			uchar &q=Binary.at<uchar>(i,j);
			if(t>128)
			{
				q=255;
			}
		}
	}
	/*dilate(Binary,Binary, Mat(), Point(-1, -1), 2, 1, 1);
	dilate(Binary,Binary, Mat(), Point(-1, -1), 2, 1, 1);
	erode(Binary,Binary, Mat(), Point(-1, -1), 2, 1, 1);
	erode(Binary,Binary, Mat(), Point(-1, -1), 2, 1, 1);
	*/
	Mat F=Binary.clone();
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(F,contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	cout<<contours.size()<<endl;
	for( int i = 0; i< contours.size(); i++ )
	{
		Mat CroppedImage;
    	bounding_rect=boundingRect(contours[i]);
    	CroppedImage=Binary(bounding_rect1);


	}

}