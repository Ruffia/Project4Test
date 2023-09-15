#include <iostream>
#include <vector>
using namespace std;

#define GetName(MARCO) #MARCO
#define MACRO1 123
#define M2     444

template<typename T1, typename T2>
void TestTempFunc()
{
	cout<<"T1"<<" "<<"T2"<<endl;
}

void ASSD()
{
	cout<<"T1"<<" "<<"T2"<<endl;
}


void Avg(float src[],float dest[], const int nCount)
{
	for (int i = 0;i< nCount;i++)
	{
		if (0 == i || 1 == i)
		{
			dest[i] = src[i];
		}
		else if (nCount - 1 == i || nCount - 2 == i )
		{
			dest[i] = src[i];
		}
		else
		{
			dest[i] = (src[i - 2] + src[i - 1] + src[i+1] + src[i+2])/4.0;
		}
	}
}

float Avg2(float src[],const int nCount)
{
	float fSum = 0;
	for (int i = 0;i< nCount;i++)
	{
		fSum += src[i];
	}

	return fSum/nCount;
}


void PlusDelta(float src[], float dest[], float delta[], float dest2[],const int nCount)
{
	Avg(src,dest,nCount);
	for (int i = 0; i < nCount;i++)
	{
		delta[i] = src[i] - dest[i];
	}

	for (int i = 0; i < nCount;i++)
	{
		dest2[i] = dest[i] + 2* delta[i];
	}
}

void PlusDelta2(float src[], float dest[], float delta[], float dest2[],const int nCount, const float fFactor)
{
	float fAvg = Avg2(src,nCount);
	for (int i = 0; i < nCount;i++)
	{
		dest[i] = src[i] - fAvg;
	}

	for (int i = 0; i < nCount;i++)
	{
		dest2[i] = dest[i]* fFactor + fAvg;
	}
}

void PlusDelta3(float src[], const int nCount, const float fFactor)
{
	float fAvg = Avg2(src,nCount);
	float* pDest = new float[nCount];
	for (int i = 0; i < nCount;i++)
	{
		pDest[i] = src[i] - fAvg;
	}

	for (int i = 0; i < nCount;i++)
	{
		float fGray = pDest[i]* fFactor + fAvg;
		fGray = fGray < 0.00f?0.00f:fGray;
		fGray = fGray > 255.f?255.f:fGray;
		src[i] = fGray;
	}

	delete[] pDest;
	pDest = NULL;
}

int main()
{
	char* s = NULL;
	s = GetName(MACRO1);
	cout<<s<<endl;

	s = GetName(M2);
	cout<<s<<endl;

	//s = GetName(TestTempFunc_int_float);
	//cout<<s<<endl;

	return 0;
}

template<class T>
float Avg(T* src,const int nCount)
{
	float fSum = 0;
	for (int i = 0;i< nCount;i++)
	{
		fSum += src[i];
	}

	return fSum/nCount;
}

template<class T>
void  Adjust(T* src, const int nCount, const float fFactor)
{
	float fAvg = Avg(src,nCount);
	float* pDest = new float[nCount];
	for (int i = 0; i < nCount;i++)
	{
		pDest[i] = src[i] - fAvg;
	}

	for (int i = 0; i < nCount;i++)
	{
		float fGray = pDest[i]* fFactor + fAvg;
		fGray = fGray < 0.00f?0.00f:fGray;
		fGray = fGray > 255.f?255.f:fGray;
		src[i] = (T)fGray;
	}

	delete[] pDest;
	pDest = NULL;
}

//int main()
//{
//	//float src[16] = {40,60,80,100,160,180,205,190,185,170,160,100,80,60,40,0};
//	float src[16] = {40,60,80,100,160,20,205,190,50,10,160,190,80,60,40,0};
//	float dest[16] = {0};
//	float dest2[16] = {0};
//	float delta[16] = {0};
//	//PlusDelta2(src,dest,delta,dest2,16,2);
//	//PlusDelta3(src,16,2.3);
//	Adjust<float>(src,16,1.0);
//	return 0;
//}