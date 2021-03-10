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
	//vec构造的向量为列向量----》》》》》多行一列

	Vec<int, 3> vi(1,2,3);//构造并且初始化3x1 3行一列
	cout <<"vi.rows =  "<< vi.rows << endl;
	cout <<"vi.cols =   " << vi.cols << endl;

	Vec<int, 4> vi1(1, 2, 3, 4);//构造4x1	4行一列
	cout << "vi1.rows =   " << vi1.rows << endl;
	cout << "vi1.cols =   " << vi1.cols << endl;
	cout << "vi1[0] = " << vi1[0] << endl;
	cout << "vi1[1] = " << vi1[1] << endl;
	cout << "vi1[2] = " << vi1[2] << endl;
	cout << "vi1[3] = " << vi1[3] << endl;

	Vec<int,2> vi2(1,2);//构造2x1  2行一列
	cout << "vi2.rows = " << vi2.rows << endl;
	cout << "vi2.cols =" << vi2.cols << endl;
	cout << "vi2[0] = " << vi2[0] << endl;
	cout << "vi2[1] = " << vi2[1] << endl;


	Vec3f point1 = Vec3f(10, 10, 3.2);//构造了一个3通道的浮点型向量
	cout << point1 << endl;

	Vec4f point2 = Vec4f(10, 10, 3.2,5);//构造了一个4通道的浮点型向量
	cout << point2 << endl;

	Vec3d point3 = Vec3d(10, 10, 3.2);//构造了一个3通道的双精度型向量
	cout << point3 << endl;


	Mat iamge = (Mat_<Vec3f>(2,2)<< Vec3f(1,2,3), Vec3f(3, 2, 3), Vec3f(9, 2, 6), Vec3f(4, 2, 7));//创造并且赋值
	for (size_t i = 0; i < iamge.rows; i++)
	{
		for (size_t j = 0; j <iamge.cols; j++)
		{
			cout << iamge.at<Vec3f>(i, j) <<endl;
		}
	}


	//构建一个2x2的矩阵 矩阵中每一个元素为三通道浮点型的点 先创建后赋值
	Mat MM = (Mat_<Vec3f>(3, 3));//2x2三通道矩阵如何赋值？？？？？？ 先创建后赋值
	for (int i = 0; i < MM.rows; i++)
	{
		for (int j = 0; j < MM.cols; j++)
		{
			for (int c = 0; c < MM.channels(); c++)
			{
				//给M的每一个元素赋值                
				MM.at<Vec3f>(i, j)[c] = c * 10;
			}
		}
	}
	cout << MM << endl;//输出矩阵


	//创建多维矩阵  自定义数据类型	
	typedef  Vec<double, 5> Vec5d;
	//生成一个2x3x5的Mat，数据为double型
	Mat M =  Mat::zeros(2, 3, CV_64FC(5));
	cout << "channel = " << M.channels() << endl;//输出为5
	for (int i = 0; i < M.rows; i++)
	{
		for (int j = 0; j < M.cols; j++)
		{
			for (int c = 0; c < M.channels(); c++)
			{
				//给M的每一个元素赋值                
				M.at<Vec5d>(i, j)[c] = c * 0.01;
			}
		}
	}
	cout << M << endl;//输出矩阵


	Mat image = Mat(500, 500, CV_8UC3);
	Mat image3 = Mat(500, 500,CV_8UC3);//构造了一张灰度图像    
	imshow("image3", image3);

	Mat image1 = Mat(500, 500, CV_8UC3, Scalar(0, 0, 255));//构造了一张红色图像  CV_8UC3
	imshow("image1", image1);

	waitKey(0);

	return 0;
}
