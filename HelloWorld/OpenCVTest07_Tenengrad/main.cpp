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

	//ͼ���ƽ���Ҷ�
	double meanValue = mean(imageSobel)[0];
	return meanValue;
}


int main()
{
	map<string,double> mapFileName2Value;
	//Ŀ���ļ���·��
	std::string strFolder = "U:/Project4Test/HelloWorld/Bin/Image/";
	std::string strFilter = "*.bmp";
	//std::string inPath = "U:/Project4Test/HelloWorld/Bin/Image/*.png";//�����ļ����µ������ļ�
	std::string inPath = strFolder + strFilter;
	//���ڲ��ҵľ��
	long handle;
	struct _finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(inPath.c_str(),&fileinfo);
	if(handle == -1) return -1;

	do
	{
		//�ҵ����ļ����ļ���
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


