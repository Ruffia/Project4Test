#include <iostream>
using namespace std;

//�Ը�����������������
float Round(const float fDecimal2Roound,const int nPrecision)
{
#define buf_size 100
	//ͨ���������ɾ����ַ��� ��%0.*f��
	char Buf[buf_size] = {0};
	sprintf_s(Buf,buf_size,"%%0.%df",nPrecision);

	//ͨ���������ɶ�Ӧ���ȵ�float�δ�ӡ���
	char outputBuf[buf_size];
	sprintf_s(outputBuf,buf_size,Buf,fDecimal2Roound);

	//��ת��float������
	float output = atof(outputBuf);
	return output;
}


//�Ը�����������������
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