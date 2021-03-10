#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

int main(int argc, char** argv) 
{
	Mat src,dst,dst1;
	src = imread("U:/Project4Test/HelloWorld/Bin/206.jpg");

	//判断图片是否载入成功
	if (src.empty()) {
		printf("图片加载失败\n");
		system("pause");
	}

	imshow("原图",src);
	cvtColor(src,dst,CV_BGR2GRAY);//转换方式1，这种是转换为灰度图，经常使用，需要记住
	cvtColor(src,dst1,COLOR_BGR2Lab);//转换方式2

	imshow("CV_BGR2GRAY转换后",dst);
	imshow("COLOR_BGR2Lab转换后",dst1);
	waitKey(0);

	return 0;

}