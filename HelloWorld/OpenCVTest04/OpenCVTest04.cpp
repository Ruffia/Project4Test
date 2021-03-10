#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#pragma comment(lib,"../OpenCV-3.2.0/x86/vc11/lib/opencv_world320d.lib")

int main(int, char **)
{
	Mat in_frame, out_frame;
	const char win1[]="Grabbing...", win2[]="Recording...";
	double fps=30;//每秒的帧数
	String file_out = "U:/Project4Test/HelloWorld/Bin/209.avi";

	VideoCapture inVid;
	bool bOpen = inVid.open(file_out) ; //打开默认摄像机
	if ( !inVid.isOpened () ) { //检查错误
		cout << "Error! Camera not ready...\n";
		return -1;
	}
	//获取输入视频的宽度和高度
	int width = (int)inVid.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)inVid.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter recVid(file_out,VideoWriter::fourcc('M','S','V','C'), fps, Size(width,height));
	if (!recVid.isOpened()) {
		cout << "Error! Video file not opened...\n";
		return -1;
	}
	//为原始视频和最终视频创建两个窗口
	namedWindow(win1);
	namedWindow(win2);
	while (true) {
		//从摄像机读取帧（抓取并解码）
		inVid >> in_frame;
		//将帧转换为灰度
		cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
		//将幀写入视频文件（编码并保存）
		recVid << out_frame;
		imshow (win1, in_frame);// 在窗口中显示帧
		imshow(win2, out_frame); // 在窗口中显示帧
		//if (waitKey(1000/fps) >= 0)
		//{
		//	break;
		//}
	}
	inVid.release(); // 关闭摄像机
	return 0;
}