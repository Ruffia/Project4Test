#include <stdio.h>
#include <iostream>
#include <io.h>
#include <string>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <map>

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

using namespace std;
using namespace cv;
using namespace std;

double GetMeanValue( std::string sImage )
{
	Mat imageSource = imread(sImage);
	Mat imageGrey;

	cvtColor(imageSource, imageGrey, CV_RGB2GRAY);
	Mat imageSobel;
	Sobel(imageGrey, imageSobel, CV_16U, 1, 1);

	//图像的平均灰度
	double meanValue = mean(imageSobel)[0];
	return meanValue;
}


int main()
{
	map<string,double> mapFileName2Value;
	//目标文件夹路径
	std::string strFolder = "U:/Project4Test/HelloWorld/Bin/Image/";
	std::string strFilter = "*.bmp";
	//std::string inPath = "U:/Project4Test/HelloWorld/Bin/Image/*.png";//遍历文件夹下的所有文件
	std::string inPath = strFolder + strFilter;
	//用于查找的句柄
	long handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(inPath.c_str(),&fileinfo);
	if(handle == -1) return -1;

	do
	{
		//找到的文件的文件名
		std::string strFileName = strFolder + fileinfo.name;
		double dMean = GetMeanValue(strFileName);
		mapFileName2Value[strFileName] = dMean;
	} while (!_findnext(handle,&fileinfo));

	_findclose(handle);

	for (map<string,double>::iterator it = mapFileName2Value.begin();
		it != mapFileName2Value.end();it++)
	{
		cout<<it->first<<"------------>"<<it->second<<endl;
	}
	system("pause");

	waitKey();
}


