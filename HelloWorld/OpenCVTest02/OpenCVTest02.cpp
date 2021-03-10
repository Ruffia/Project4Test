#include <opencv2/opencv.hpp>
#include <iostream>

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

using namespace std;
using namespace cv;
int main(int, char *argv[])
{
	Mat in_image, out_image;
	// Usage： <cmd> <file_in> <file_out>
	//读取原始图像

	const cv::String strInputImageName = "U:/Project4Test/HelloWorld/Bin/101.jpg";
	const cv::String strOutputImageName = "U:/Project4Test/HelloWorld/Bin/101-copy.jpg";
	in_image = imread(strInputImageName, IMREAD_UNCHANGED);
	if (in_image.empty()) {
		//检查是否读取图像
		cout << "Error! Input image cannot be read...\n";
		return -1;
	}
	//创建两个具有图像名称的窗口
	namedWindow(strInputImageName, WINDOW_AUTOSIZE);
	namedWindow(strOutputImageName, WINDOW_AUTOSIZE);
	//在之前创建的窗口中显示图片
	imshow(strInputImageName, in_image);
	cvtColor(in_image, out_image, COLOR_BGR2GRAY);
	imshow(strOutputImageName, in_image);
	cout << "Press any key to exit...\n";
	waitKey(); // Wait for key press
	//写入图像
	imwrite(strOutputImageName, in_image);
	return 0;
}