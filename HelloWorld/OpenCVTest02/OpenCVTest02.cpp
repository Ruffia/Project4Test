#include <opencv2/opencv.hpp>
#include <iostream>

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

using namespace std;
using namespace cv;
int main(int, char *argv[])
{
	Mat in_image, out_image;
	// Usage�� <cmd> <file_in> <file_out>
	//��ȡԭʼͼ��

	const cv::String strInputImageName = "U:/Project4Test/HelloWorld/Bin/101.jpg";
	const cv::String strOutputImageName = "U:/Project4Test/HelloWorld/Bin/101-copy.jpg";
	in_image = imread(strInputImageName, IMREAD_UNCHANGED);
	if (in_image.empty()) {
		//����Ƿ��ȡͼ��
		cout << "Error! Input image cannot be read...\n";
		return -1;
	}
	//������������ͼ�����ƵĴ���
	namedWindow(strInputImageName, WINDOW_AUTOSIZE);
	namedWindow(strOutputImageName, WINDOW_AUTOSIZE);
	//��֮ǰ�����Ĵ�������ʾͼƬ
	imshow(strInputImageName, in_image);
	cvtColor(in_image, out_image, COLOR_BGR2GRAY);
	imshow(strOutputImageName, in_image);
	cout << "Press any key to exit...\n";
	waitKey(); // Wait for key press
	//д��ͼ��
	imwrite(strOutputImageName, in_image);
	return 0;
}