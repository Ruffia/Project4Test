#include <iostream>
using namespace std;
#include <windows.h>

typedef struct tagStatusVac{
	WORD	Y2QP	: 2;	// 00000000 0000??00
	WORD	Y2MK	: 2;	// 00000000 000000??
	WORD	X2		: 4;	// 00000000 ????0000
	WORD	Y1QP	: 2;	// ??000000 00000000
	WORD	Y1K		: 1;	// 00?00000 00000000
	WORD	Y1M		: 1;	// 000?0000 00000000
	WORD	X1		: 4;	// 0000???? 00000000
}StatusVac;


typedef union tagStatusVacConvertor
{
	WORD			wStatus;
	StatusVac	status;	
}StatusVacConvertor;



typedef struct tagLRCCheck{
	char	cHigh	: 4;	// 0000????
	char	cLow	: 4;	// ????0000
}LRCCheck;


typedef union tagLRC
{
	BYTE	bData;
	LRCCheck status;	
}LRC;


int main()
{
	//StatusVacConvertor v;
	//v.wStatus = 29;

	//int status1 = 0x98;
	//BYTE	bX = (status1 & 0xF0) >> 4;					// ��4λ�еĵ�3λ��ʾX
	//int n = bX;
	//BOOL	bYm = ( (status1 & 0x08) == 0x08 );	// ��4λ��ʾY���������λΪ1��ʾǹ��մ���״̬
	//BOOL	bYk = ( (status1 & 0x04) == 0x04 );	// ��4λ��ʾY�����дθ�λΪ1��ʾ��Ʒ����մ���״̬

	LRC rc;
	rc.bData = 0x45;

	return 0;
}