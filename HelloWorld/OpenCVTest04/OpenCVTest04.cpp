#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

int main(int, char **)
{
	Mat in_frame, out_frame;
	const char win1[]="Grabbing...", win2[]="Recording...";
	double fps=30;//ÿ���֡��
	String file_out = "U:/Project4Test/HelloWorld/Bin/209.avi";

	VideoCapture inVid;
	bool bOpen = inVid.open(file_out) ; //��Ĭ�������
	if ( !inVid.isOpened () ) { //������
		cout << "Error! Camera not ready...\n";
		return -1;
	}
	//��ȡ������Ƶ�Ŀ�Ⱥ͸߶�
	int width = (int)inVid.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)inVid.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter recVid(file_out,VideoWriter::fourcc('M','S','V','C'), fps, Size(width,height));
	if (!recVid.isOpened()) {
		cout << "Error! Video file not opened...\n";
		return -1;
	}
	//Ϊԭʼ��Ƶ��������Ƶ������������
	namedWindow(win1);
	namedWindow(win2);
	while (true) {
		//���������ȡ֡��ץȡ�����룩
		inVid >> in_frame;
		//��֡ת��Ϊ�Ҷ�
		cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
		//����д����Ƶ�ļ������벢���棩
		recVid << out_frame;
		imshow (win1, in_frame);// �ڴ�������ʾ֡
		imshow(win2, out_frame); // �ڴ�������ʾ֡
		//if (waitKey(1000/fps) >= 0)
		//{
		//	break;
		//}
	}
	inVid.release(); // �ر������
	return 0;
}