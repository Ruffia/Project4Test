#include <iostream>
using namespace std;

//对浮点数进行四舍五入
float Round(const float fDecimal2Roound,const int nPrecision)
{
#define buf_size 100
	//通过输入生成精度字符串 （%0.*f）
	char Buf[buf_size] = {0};
	sprintf_s(Buf,buf_size,"%%0.%df",nPrecision);

	//通过输入生成对应精度的float形打印输出
	char outputBuf[buf_size];
	sprintf_s(outputBuf,buf_size,Buf,fDecimal2Roound);

	//回转回float行数据
	float output = atof(outputBuf);
	return output;
}


//对浮点数进行四舍五入
float Round2(const float fDecimal2Roound,const int nPrecision)
{
	float fDelta = 0.5f;
	for(int i = 0; i<nPrecision; i++)
	{
		fDelta = fDelta * 0.1;
	}

	int n = 1;
	for(int i = 0; i<nPrecision; i++)
	{
		n = n * 10;
	}

	int nInteger = (fDecimal2Roound + fDelta)* n;
	float fTemp = nInteger * 1.f /n;
	return fTemp;
}

int main()
{
	float f2Round = 3.62569;
	int nPrecision = 3;
	float f = Round2(f2Round,nPrecision);
	cout<<"f2Round = "<<f2Round<< "  Precision = "<<nPrecision<<" Result = "<<f<<endl;
	return 0;
}