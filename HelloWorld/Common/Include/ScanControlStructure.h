// ScanControlStructure.h :
//

#if !defined(_ScanControlStructure_H_)
#define _ScanControlStructure_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const DWORD			ThreadSwitchOptionTime			= 5;	// ms
const DWORD			ThreadSwitchOptionTime_USB		= 8;	// ms
/*
// ADDRESS[9��2]	CONTENT      ( bit31--------------------------------------------------------bit0)
// =================================================================================================
// 10000001B	ENABLE   ��bit0��
// 10000010B	FLAG[30..28],[27],MODEL[26..24],[23],AVE[22..20],RESO[19..18],FREDIV[17..0]��bit0��
// 10000011B	DOT0X[23..12],DOT0Y[11..0]
// 10000100B	POINTX[23..12],POINTY[11..0]
// 10000101B	STEPX[24..0]
// 10000110B	STEPY[24..0]
// 10000111B	FIFO_OFFSET[31..0]
// 10001000B	COMA[7..4][1..0]
// 10001001B	COMB[7..4][1..0]

// FIFO_OFFSET_FULL
// FIFO_OFFSET_EMPTY
// ld[31..24]          ld[23..16]          ld[15..8]               ld[7..0]
// full_offset��8λ    full_offset��8λ    empty_offset��8λ        empty_offset��8λ

typedef struct tagInitData_ADDR_10000001B{
	DWORD	ENABLE		: 1;	// 00000000 00000000 00000000 0000000?
	DWORD	PHOTO_ENABLE: 1;	// 00000000 00000000 00000000 000000?0
	DWORD	reserve1	: 30;	// ???????? ???????? ???????? ??????00
}InitData_ADDR_10000001B;

typedef struct tagInitData_ADDR_10000010B{
	DWORD	FREDIV		: 18;	// 00000000 000000?? ???????? ????????
	DWORD	RESO		: 2;	// 00000000 0000??00 00000000 00000000
	DWORD	AVE			: 3;	// 00000000 0???0000 00000000 00000000
	DWORD	reserve1	: 1;	// 00000000 ?0000000 00000000 00000000
	DWORD	MODEL		: 3;	// 00000??? 00000000 00000000 00000000
	DWORD	reserve2	: 1;	// 0000?000 00000000 00000000 00000000
	DWORD	FLAG		: 3;	// 0???0000 00000000 00000000 00000000
	DWORD	reserve3	: 1;	// ?0000000 00000000 00000000 00000000
}InitData_ADDR_10000010B;

typedef struct tagInitData_ADDR_10000011B{
	DWORD	DOT0Y		: 12;	// 00000000 00000000 0000???? ????????
	DWORD	DOT0X		: 12;	// 00000000 ???????? ????0000 00000000
	DWORD	reserve1	: 8;	// ???????? 00000000 00000000 00000000
}InitData_ADDR_10000011B;

typedef struct tagInitData_ADDR_10000100B{
	DWORD	POINTY		: 12;	// 00000000 00000000 0000???? ????????
	DWORD	POINTX		: 12;	// 00000000 ???????? ????0000 00000000
	DWORD	reserve1	: 8;	// ???????? 00000000 00000000 00000000
}InitData_ADDR_10000100B;

typedef struct tagInitData_ADDR_10000101B{
	DWORD	STEPX		: 24;	// 00000000 ???????? ???????? ????????
	DWORD	STEPX_F		: 1;	// 0000000? 00000000 00000000 00000000
	DWORD	reserve1	: 7;	// ???????0 00000000 00000000 00000000
}InitData_ADDR_10000101B;

typedef struct tagInitData_ADDR_10000110B{
	DWORD	STEPY		: 24;	// 00000000 ???????? ???????? ????????
	DWORD	STEPY_F		: 1;	// 0000000? 00000000 00000000 00000000
	DWORD	reserve1	: 7;	// ???????0 00000000 00000000 00000000
}InitData_ADDR_10000110B;

typedef struct tagInitData_ADDR_10000111B{
	DWORD	FIFO_EMPTY	: 16;	// 00000000 00000000 ???????? ????????
	DWORD	FIFO_FULL	: 16;	// ???????? ???????? 00000000 00000000
}InitData_ADDR_10000111B;

typedef struct tagInitData{
	InitData_ADDR_10000001B		ADDR_10000001B;		// ADDRESS[9��2] : 10000001B
	InitData_ADDR_10000010B		ADDR_10000010B;		// ADDRESS[9��2] : 10000010B
	InitData_ADDR_10000011B		ADDR_10000011B;		// ADDRESS[9��2] : 10000011B
	InitData_ADDR_10000100B		ADDR_10000100B;		// ADDRESS[9��2] : 10000100B
	InitData_ADDR_10000101B		ADDR_10000101B;		// ADDRESS[9��2] : 10000101B
	InitData_ADDR_10000110B		ADDR_10000110B;		// ADDRESS[9��2] : 10000110B
	InitData_ADDR_10000111B		ADDR_10000111B;		// ADDRESS[9��2] : 10000111B
}InitData;

typedef union tagInitParam
{
	DWORD		dwData[7];	// �������ݱ�
	InitData	Data;		// �������ݽṹ
}InitParam;

// ADDRESS[9��2]	CONTENT      ( bit31--------------------------------------------------------bit0)
// =================================================================================================
// 10000110B	LENS[7..4][1..0]
// 10000111B	SCAN[7..4][1..0]
// 10001000B	OVERFLOW[28], DACX[27..16], FIFO_NUM[15..0]
// 10001001B	DACY[11..0]

typedef struct tagReadData_ADDR_10001000B{
	DWORD	FIFO_NUM	: 16;	// 00000000 00000000 ???????? ????????
	DWORD	DACX		: 12;	// 0000???? ???????? 00000000 00000000
	DWORD	OVERFLOW	: 1;	// 000?0000 00000000 00000000 00000000
	DWORD	reserve1	: 3;	// ???00000 00000000 00000000 00000000
}ReadData_ADDR_10001000B;

typedef struct tagReadData_ADDR_10001001B{
	DWORD	DACY		: 12;	// 00000000 00000000 0000???? ????????
	DWORD	reserve1	: 4;	// 00000000 00000000 ????0000 00000000
	DWORD	PHOTO_FIFO	: 1;	// 00000000 0000000? 00000000 00000000
	DWORD	reserve2	: 15;	// ???????? ???????0 00000000 00000000
}ReadData_ADDR_10001001B;


/////////////////////////////////////////////////////////////////////////////
// ��FIFO /AF (almost full) ������������
// FLAG				2,	   1,	 3,	   6,	 4,    5,	7,   0
// FIFO SIZE		16384, 8192, 4096, 2048, 1024, 512, 256, 128
//---------------------------------------------------------------------------
const DWORD	FLAG_FIFO_SIZE[] = 
	{ 128, 8192, 16384, 4096, 1024, 512, 2048, 256, };
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// AVE[22..20]			ƽ���˲��ֵ�����0~7��
// RESO [19, 18]        �ֱ��ʷֵ�����0~3��
// FREDIV [17, 0]		���������Ƶ����1~2p18-1��
// �ɵ�ͣ��ʱ��tpȷ��AVE��FREDIV
// �ٸ��ݲɼ����ٶȼ���ʾƵ�ʣ�ȷ����FIFO /AF (almost full) ������������FLAG
/////////////////////////////////////////////////////////////////////////////
// (��ͣ��ʱ��tp	��λ:ns)
// FREDIV = (tp/50ns - 13) / (POWER(2,AVE+1) + 3) - 1			AVE = 1-7 ;
// FREDIV =	1													AVE = 0	  ;
//---------------------------------------------------------------------------
// (��ͣ��ʱ��tp	��λ:ns)	AVE = 7
//						==>		FREDIV = (tp*20 - 13) / 259 - 1
/////////////////////////////////////////////////////////////////////////////
// ��������ֵ(�ٶ�ÿ���Ӳɼ�50��)
// tp		1us	 2us 5us 10us 16us 20us 40us 1ms  10ms  100ms
// AVE		0,	 1,	 2,	 3,	  5,   6,	7,	 7,   7,    7,   
// FREDIV	1,	 3,	 7,	 9,	  4,   2,	2,	 4CH, 303H, 1E28H,
// FLAG		2,	 1,	 3,	 6,	  4,   4,	5,	 0,   0,    0,
//---------------------------------------------------------------------------
// tp		40us 80us 120us 160us	50us 90us	���ೣ��ֵ
// AVE		 7,   7,   7,    7,      7,   7, 
// FREDIV	 2,   5,   8,   11,      3,   6,
// FLAG		 5,   5,   5,    5,      5,   5,
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// ��ͣ��ʱ�䳣��ֵ��
/////////////////////////////////////////////////////////////////////////////
typedef enum tagScanSpeed
{
	SS_1us				= 0,	// ��ͣ��ʱ��   1us
	SS_2us				= 1,	// ��ͣ��ʱ��   2us
	SS_5us				= 2,	// ��ͣ��ʱ��   5us
	SS_10us				= 3,	// ��ͣ��ʱ��  10us
	SS_16us				= 4,	// ��ͣ��ʱ��  16us
	SS_20us				= 5,	// ��ͣ��ʱ��  20us
	SS_40us				= 6,	// ��ͣ��ʱ��  40us
	SS_80us				= 7,	// ��ͣ��ʱ��  80us
	SS_120us			= 8,	// ��ͣ��ʱ�� 120us
	SS_160us			= 9,	// ��ͣ��ʱ�� 160us
}ScanSpeed;

/////////////////////////////////////////////////////////////////////////////
const DWORD	SCANSPEED_TP[]		= {	1,  2,  5, 10, 16, 20, 40, 80, 120, 160, };
const DWORD	INITDATA_AVE[]		= {	0,	1,	2,	3,	5,	6,  7,  7,   7,   7, };
const DWORD	INITDATA_FREDIV[]	= {	1,	3,	7,	9,	4,	2,	2,	5,   8,  11, };
const DWORD	INITDATA_FLAG[]		= {	3,	6,	4,	4,	5,	0,	0,	0,	 0,   0, };
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

typedef union tagReadParam
{
	DWORD	dwParam;		// ��������

	// �������ݽṹ
	ReadData_ADDR_10001000B		ADDR_10001000B;		// ADDRESS[9��2] : 10001000B
	ReadData_ADDR_10001001B		ADDR_10001001B;		// ADDRESS[9��2] : 10001001B
}ReadParam;

const DWORD ADDR_10000000B = 0x00;
const DWORD ADDR_10000001B = 0x04;
const DWORD ADDR_10001000B = 0x20;
const DWORD ADDR_10001001B = 0x24;
/*
//////////////////////////////////////////////////////////////////////
// �ɼ���֧�ֵ����ֹ�����ʽ��
// ��ɨ(ȫ��/ѡ��)����ɨ��˫�š�ͼ��ָģ�����ࡢ��������
typedef enum tagScanFunction
{
	SF_Stop					= 0,	// ֹͣ
	SF_RasterScan			= 1,	// ��ɨ	001B
	SF_LineScan				= 2,	// ��ɨ	010B
	SF_DualMagnification	= 3,	// ˫��	011B
	SF_SplitScan			= 4,	// �ָ�	100B
	SF_AnalogPhoto			= 5,	// ģ������	101B
	SF_DigitalPhoto			= 6,	// ��������	110B
}ScanFunction;

// �ɼ���֧�ֵ����ֱַ��ʣ�
//		 512 * 384
//		1024 * 768
//		2048 * 1536
//		4096 * 3072
typedef enum tagScanResolution
{
	SR_512x384				= 0,	//  512 *  384 �ֱ���
	SR_1024x768				= 1,	// 1024 *  768 �ֱ���
	SR_2048x1536			= 2,	// 2048 * 1536 �ֱ���
	SR_4096x3072			= 3,	// 4096 * 3072 �ֱ���
}ScanResolution;

const LONG ScanResolution_X_Pixels[] = { 512, 1024, 2048, 4096, };

// ��ɨ��( ��ͣ��ʱ�䣬�ֱ��ʣ�) ��ʼ�����꣬��ֹ������
typedef struct tagExtrParamRasterScan
{
	LONG	dwStartX;	// ��ʼ�� X ����
	LONG	dwStartY;	// ��ʼ�� Y ����
	LONG	dwStopX;	// ��ֹ�� X ����
	LONG	dwStopY;	// ��ֹ�� Y ����
}ExtrParamRasterScan;

// ��ɨ��( ��ͣ��ʱ�䣬�ֱ��ʣ�) ��ʼ�����꣬��ֹ�����꣬��ɨ����
typedef struct tagExtrParamLineScan
{
	LONG	dwStartX;		// ��ʼ�� X ����
	LONG	dwStartY;		// ��ʼ�� Y ����
	LONG	dwStopX;		// ��ֹ�� X ����
	LONG	dwStopY;		// ��ֹ�� Y ����
	LONG	dwPixelNumber;	// ��ɨ����
}ExtrParamLineScan;

// ˫�ţ�(��ͣ��ʱ�䣬 �ֱ��� = 1024 * 768 )
//		С������ʼ�����꣬С������ֹ������
typedef struct tagExtrParamDualMagnification
{
	LONG	dwStartX;	// С������ʼ�� X ����
	LONG	dwStartY;	// С������ʼ�� Y ����
	LONG	dwStopX;	// С������ֹ�� X ���� (����)
	LONG	dwStopY;	// С������ֹ�� Y ����
}ExtrParamDualMagnification;

typedef union tagScanParam
{
	ExtrParamDualMagnification	DualMag;		// ˫�Ų���
	ExtrParamLineScan			LineScan;		// ��ɨ����
	ExtrParamRasterScan			RasterScan;		// ��ɨ����
}ScanParam;
*/
// ͼ��ָ��ͣ��ʱ��( ,�ֱ��� = 1024 * 768 )
// ģ�����ࣺ��ͣ��ʱ��( ,�ֱ��� = 1024 * 768 )
// �������ࣺ��ͣ��ʱ��( ,�ֱ��� = 1024 * 768 )
//////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
// USB
/////////////////////////////////////////////////////////////////////
/*
// ɨ���ٶ�
typedef enum tagUSB_ScanSpeed
{
	USB_SS_125ns			= 0,
	USB_SS_250ns			= 1,
	USB_SS_500ns			= 2,
	USB_SS_1us				= 3,
	USB_SS_2us				= 4,
	USB_SS_4us				= 5,
	USB_SS_5us				= 6,
	USB_SS_8us				= 7,
	USB_SS_10us				= 8,
	USB_SS_12us				= 9,
	USB_SS_16us				= 10,
	USB_SS_20us				= 11,
	USB_SS_25us				= 12,
	USB_SS_30us				= 13,
	USB_SS_32us				= 14,
	USB_SS_35us				= 15,
	USB_SS_40us				= 16,
	USB_SS_50us				= 17,
	USB_SS_60us				= 18,
	USB_SS_63750ns			= 19,
	USB_SS_64us				= 20,
	USB_SS_70us				= 21,
	USB_SS_80us				= 22,
	USB_SS_90us				= 23,
	USB_SS_100us			= 24,
	USB_SS_110us			= 25,
	USB_SS_120us			= 26,
	USB_SS_130us			= 27,
	USB_SS_140us			= 28,
	USB_SS_150us			= 29,
	USB_SS_160us			= 30,
}USB_ScanSpeed;
*/
typedef struct tagUSB_InitRampParam
{
	WORD	wOffset;
	WORD	wValley;
	WORD	wRise;
	WORD	wDRise;
	WORD	wPeak;
	WORD	wFall;
	WORD	wDFall;
//	WORD	wDirection;
}USB_InitScanRampParam;

typedef struct tagUSB_InitData
{
	USB_InitScanRampParam	ScanRampParamX;
	USB_InitScanRampParam	ScanRampParamY;
	unsigned short			PixRate;
}USB_InitData;

typedef union tagUSB_InitParam
{
	WORD			wData[14];	// �������ݱ�
	USB_InitData	Data;		// �������ݽṹ
}USB_InitParam;

// ��ɨ��( ��ͣ��ʱ�䣬�ֱ��ʣ�) ��ʼ�����꣬��ֹ������
typedef struct tagUSB_ExtrParamRasterScan
{
	LONG	dwStartX;	// ��ʼ�� X ����
	LONG	dwStartY;	// ��ʼ�� Y ����
	LONG	dwStopX;	// ��ֹ�� X ����
	LONG	dwStopY;	// ��ֹ�� Y ����
}USB_ExtrParamRasterScan;

// ��ɨ��( ��ͣ��ʱ�䣬�ֱ��ʣ�) ��ʼ�����꣬��ֹ�����꣬��ɨ����
typedef struct tagUSB_ExtrParamLineScan
{
	LONG	dwStartX;		// ��ʼ�� X ����
	LONG	dwStartY;		// ��ʼ�� Y ����
	LONG	dwStopX;		// ��ֹ�� X ����
	LONG	dwStopY;		// ��ֹ�� Y ����
	LONG	dwPixelNumber;	// ��ɨ����
}USB_ExtrParamLineScan;

// ˫�ţ�(��ͣ��ʱ�䣬 �ֱ��� = 1024 * 768 )
//		С������ʼ�����꣬С������ֹ������
typedef struct tagUSB_ExtrParamDualMagnification
{
	LONG	dwStartX;	// С������ʼ�� X ����
	LONG	dwStartY;	// С������ʼ�� Y ����
	LONG	dwStopX;	// С������ֹ�� X ���� (����)
	LONG	dwStopY;	// С������ֹ�� Y ����
}USB_ExtrParamDualMagnification;

typedef union tagUSB_ScanParam
{
	USB_ExtrParamDualMagnification	DualMag;		// ˫�Ų���
	USB_ExtrParamLineScan			LineScan;		// ��ɨ����
	USB_ExtrParamRasterScan			RasterScan;		// ��ɨ����
}USB_ScanParam;

// �ɼ���֧�ֵ����ֹ�����ʽ��
// ��ɨ��ѡ������ɨ����ɨ��ģ������

typedef enum tagUSB_ScanFunction
{
	USB_SF_Stop					= 0,	// ֹͣ
	USB_SF_RasterScan			= 1,	// ��ɨ
	USB_SF_AreaScan				= 2,	// ѡ��
	USB_SF_LineScan_HORZ		= 3,	// ˮƽ��ɨ
	USB_SF_LineScan_VERT		= 4,	// ��ֱ��ɨ
	USB_SF_SpotScan				= 5,	// ��ɨ
	USB_SF_AnalogPhoto			= 6,	// ģ������
}USB_ScanFunction;

typedef enum tagUSB_ScanType
{
	USB_ST_Stop					= 0,	// ����ͼ��ɨ��
	USB_ST_RasterScan			= 1,	// ����ɨ��
	USB_ST_AreaScan				= 2,	// ѡ��ɨ��
	USB_ST_LineScan_HORZ		= 3,	// ˮƽ��ɨ��
	USB_ST_LineScan_VERT		= 4,	// ��ֱ��ɨ��
	USB_ST_SpotScan				= 5,	// ��ɨ��
	USB_ST_AnalogPhoto			= 6,	// ģ������
	USB_ST_AutoBCArea			= 7,	// �̶�ѡ��ɨ��	AutoBC
	USB_ST_AutoFocusArea		= 8,	// �̶�ѡ��ɨ��	AutoFocus
	USB_ST_AutoAstigmatArea		= 9,	// �̶�ѡ��ɨ�� AutoAstigmat
	USB_ST_Max					=10,	// Max
}USB_ScanType;

/*
/////////////////////////////////////////////////////////////////////////////
// Pixel rate in units of 1/8 MHz, namely 125ns.
// Pixel rate = N means N * 125nS for pixel time
// The range of N is from 1 to 2K, namely 1,2,3,...0x7FF
/////////////////////////////////////////////////////////////////////////////
// ��������ֵ�������ʼ��㶺��ʱ��
// tp		0.125us 0.250us 0.5us 1us  2us  5us 10us 16us 20us 40us 80us 100us 120us 160us 200us 250us
// N		1,      2,      4,    8,   16,  40, 80,  128, 160, 320, 640, 800,  960,  1280, 1600, 2000
//---------------------------------------------------------------------------
// tp		40us 80us 120us 160us	50us 90us	���ೣ��ֵ
// N		320, 640, 960,  1280,   400, 720
/////////////////////////////////////////////////////////////////////////////

//                                  500n	1us	2us	3	4us		8us		11		16us	19		20us	22		23		27		32us	36	37		40us   48us	 55		64us	72		80us	90		100us	110		120us	128us	140us  160us	180		200us	220		240us	255us	256us	280us  320us  360us	400us	440us	480us	512us   560us	600us	640us
const WORD	USB_PIXEL_RATES[]	= {	1,		2,  4,	6,	8,		16,		22,		32,		38,		40,		44,		46,		54,		64,		72,	74,		80,    96,	 110,	128,	144,	160,	180,	200,	220,	240,	256,	280,   320,		360,	400,	440,	480,	510,	512,	560,   640,   720,	800,	880,	960,    1240,	1120,	1200,	1280, };
const DWORD	USB_SCANSPEED_TP[]	= {	125,	250,500,750,1000,	2000,	2750,	4000,	4750,	5000,	5500,	5750,	6750,	8000,	9000,9250,	10000, 12000,13750,	16000,	18000,	20000,	22500,	25000,	27500,	30000,	32000,	35000, 40000,	45000,	50000,	55000,	60000,  63750,	64000,	70000, 80000, 90000,100000, 110000, 120000, 128000, 140000, 150000, 160000, };	// unit: ns

//										0.125us 0.25us 0.5us 1us   2us   5us   10us   16us   20us	40us	80us   120us   160us
//	const WORD	USB_PIXEL_RATES[]	= {	1,      2,     4,    8,    16,   40,   80,    128,   160,	320,	640,   960,    1280, };
//	const DWORD	USB_SCANSPEED_TP[]	= {	125,    250,   500,  1000, 2000, 5000, 10000, 16000, 20000, 40000, 80000, 120000, 160000, };	// unit: ns

// MCI���õķֱ��ʣ�
typedef enum tagUSB_ScanResolution
{
	SR_16x16				= 0,
	SR_32x32				= 1,
	SR_64x64				= 2,
	SR_128x128				= 3,
	SR_256x256				= 4,
	SR_512x512				= 5,	//  512 *  512 �ֱ���
	SR_1024x1024			= 6,	// 1024 * 1024 �ֱ���
	SR_2048x2048			= 7,	// 2048 * 2048 �ֱ���
	SR_4096x4096			= 8,	// 4096 * 4096 �ֱ���
	SR_8192x8192			= 9,	// 8192 * 8192 �ֱ���
	SR_1x1					= 10,
}USB_ScanResolution;
*/
#endif // _ScanControlStructure_H_
