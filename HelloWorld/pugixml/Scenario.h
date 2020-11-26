#pragma once

class Scenario
{
public:
	Scenario();
    void Reset(); 

public:
	char szSampleName[256];      //��Ʒ����
	char szCreateTime[64];       //��������ʱ��
	char szAuthorName[64];       //��������
	char szDescription[256];     //��������
	int  HVType;                 //��ѹ����CPS����Spellman
	double HV;                   //��ѹֵ
	double Bias;                 //ƫѹ��������
	double FilamentCurrent;      //��˿����
	double Contrast;             //�Աȶ�
	double Brightness;           //����
	double CondenserLens;        //�۹⾵
	double ObjectiveLens;        //�ﾵ
	double Magnifier;            //�Ŵ���	
	double BeemAlignmentX;       //�����X
	double BeemAlignmentY;       //�����Y
	double StigmatorX;           //����ɢX
	double StigmatorY;           //����ɢY
};