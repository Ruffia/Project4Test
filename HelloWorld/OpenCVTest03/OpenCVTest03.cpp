#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

int main(int argc, char** argv) 
{
	Mat src,dst,dst1;
	src = imread("U:/Project4Test/HelloWorld/Bin/206.jpg");

	//�ж�ͼƬ�Ƿ�����ɹ�
	if (src.empty()) {
		printf("ͼƬ����ʧ��\n");
		system("pause");
	}

	imshow("ԭͼ",src);
	cvtColor(src,dst,CV_BGR2GRAY);//ת����ʽ1��������ת��Ϊ�Ҷ�ͼ������ʹ�ã���Ҫ��ס
	cvtColor(src,dst1,COLOR_BGR2Lab);//ת����ʽ2

	imshow("CV_BGR2GRAYת����",dst);
	imshow("COLOR_BGR2Labת����",dst1);
	waitKey(0);

	return 0;

}