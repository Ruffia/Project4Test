#include "Scenario.h"

Scenario::Scenario()
{
	Reset();
}

void Scenario::Reset() 
{
	for (int i = 0; i < 256; i++)
	{
		szSampleName[i] = 0;
	}

	for (int i = 0; i < 64; i++)
	{
		szCreateTime[i] = 0;
	}

	for (int i = 0; i < 64; i++)
	{
		szAuthorName[i] = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		szDescription[i] = 0;
	}

	HVType = 0;                 //��ѹ����CPS����Spellman
	HV = 0.0;                   //��ѹֵ
	Bias = 0.0;                 //ƫѹ��������
	FilamentCurrent = 0.0;      //��˿����
	Contrast = 0.0;             //�Աȶ�
	Brightness = 0.0;           //����
	CondenserLens = 0.0;        //�۹⾵
	ObjectiveLens = 0.0;        //�ﾵ
	Magnifier = 0.0;            //�Ŵ���	
	BeemAlignmentX = 0.0;       //�����X
	BeemAlignmentY = 0.0;       //�����Y
	StigmatorX = 0.0;           //����ɢX
	StigmatorY = 0.0;           //����ɢY
}