//∂¡»°Õº∆¨≤¢œ‘ æ
#include "stdio.h"
#include<iostream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
using namespace cv;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

int main()
{
	Mat img = imread("U:/Project4Test/HelloWorld/Bin/101.jpg");
	namedWindow("≤‚ ‘opencv");
	imshow("≤‚ ‘opencv", img);
	cvWaitKey(6000);
	return 0;
}
