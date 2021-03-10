#include "opencv/cv.h" 
#include "opencv/highgui.h" 
#include "opencv/cxcore.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")


int main()
{
	Vec<int, 3> vi0;
	//vec���������Ϊ������----��������������һ��

	Vec<int, 3> vi(1,2,3);//���첢�ҳ�ʼ��3x1 3��һ��
	cout <<"vi.rows =  "<< vi.rows << endl;
	cout <<"vi.cols =   " << vi.cols << endl;

	Vec<int, 4> vi1(1, 2, 3, 4);//����4x1	4��һ��
	cout << "vi1.rows =   " << vi1.rows << endl;
	cout << "vi1.cols =   " << vi1.cols << endl;
	cout << "vi1[0] = " << vi1[0] << endl;
	cout << "vi1[1] = " << vi1[1] << endl;
	cout << "vi1[2] = " << vi1[2] << endl;
	cout << "vi1[3] = " << vi1[3] << endl;

	Vec<int,2> vi2(1,2);//����2x1  2��һ��
	cout << "vi2.rows = " << vi2.rows << endl;
	cout << "vi2.cols =" << vi2.cols << endl;
	cout << "vi2[0] = " << vi2[0] << endl;
	cout << "vi2[1] = " << vi2[1] << endl;


	Vec3f point1 = Vec3f(10, 10, 3.2);//������һ��3ͨ���ĸ���������
	cout << point1 << endl;

	Vec4f point2 = Vec4f(10, 10, 3.2,5);//������һ��4ͨ���ĸ���������
	cout << point2 << endl;

	Vec3d point3 = Vec3d(10, 10, 3.2);//������һ��3ͨ����˫����������
	cout << point3 << endl;


	Mat iamge = (Mat_<Vec3f>(2,2)<< Vec3f(1,2,3), Vec3f(3, 2, 3), Vec3f(9, 2, 6), Vec3f(4, 2, 7));//���첢�Ҹ�ֵ
	for (size_t i = 0; i < iamge.rows; i++)
	{
		for (size_t j = 0; j <iamge.cols; j++)
		{
			cout << iamge.at<Vec3f>(i, j) <<endl;
		}
	}


	//����һ��2x2�ľ��� ������ÿһ��Ԫ��Ϊ��ͨ�������͵ĵ� �ȴ�����ֵ
	Mat MM = (Mat_<Vec3f>(3, 3));//2x2��ͨ��������θ�ֵ������������ �ȴ�����ֵ
	for (int i = 0; i < MM.rows; i++)
	{
		for (int j = 0; j < MM.cols; j++)
		{
			for (int c = 0; c < MM.channels(); c++)
			{
				//��M��ÿһ��Ԫ�ظ�ֵ                
				MM.at<Vec3f>(i, j)[c] = c * 10;
			}
		}
	}
	cout << MM << endl;//�������


	//������ά����  �Զ�����������	
	typedef  Vec<double, 5> Vec5d;
	//����һ��2x3x5��Mat������Ϊdouble��
	Mat M =  Mat::zeros(2, 3, CV_64FC(5));
	cout << "channel = " << M.channels() << endl;//���Ϊ5
	for (int i = 0; i < M.rows; i++)
	{
		for (int j = 0; j < M.cols; j++)
		{
			for (int c = 0; c < M.channels(); c++)
			{
				//��M��ÿһ��Ԫ�ظ�ֵ                
				M.at<Vec5d>(i, j)[c] = c * 0.01;
			}
		}
	}
	cout << M << endl;//�������


	Mat image = Mat(500, 500, CV_8UC3);
	Mat image3 = Mat(500, 500,CV_8UC3);//������һ�ŻҶ�ͼ��    
	imshow("image3", image3);

	Mat image1 = Mat(500, 500, CV_8UC3, Scalar(0, 0, 255));//������һ�ź�ɫͼ��  CV_8UC3
	imshow("image1", image1);

	waitKey(0);

	return 0;
}
