
#ifndef __VACObtain_H
#define __VACObtain_H

#define WM_USER_VAC_UpdateStatus	(WM_USER	+57)	// Status byte from the controller is passed to user via the wParam argument
#define WM_USER_VAC_UpdateValue		(WM_USER	+58)
#define WM_USER_VAC_UpdateIPGValue	(WM_USER	+59)
#define WM_USER_VAC_UpdateIPCValue	(WM_USER	+60)
#define WM_USER_VAC_UpdateCCGValue	(WM_USER	+61)

#define EPSILON_E11 (float)(1E-11)
#define EPSILON_E9 (float)(1E-9)
#define EPSILON_E7 (float)(1E-7)
#define EPSILON_E5 (float)(1E-5)

typedef struct tagVACcfg_CCGIPG{
	int				nPortIPG;		// IPG COM�˿ں�
	int				nPortIPC;		// IPC COM�˿ں�
	int				nPortCCG;		// CCG COM�˿ں�
	BOOL			bIPGready;
	BOOL			bIPCready;
	BOOL			bCCGready;
	double			dVacIPG;		// IPG���ֵ
	double			dVacIPC;
	double			dVacCCG;
} CfgVAC_CCGIPG;

typedef struct tagVACcfg_IP_CCG{
	double			dVac;			// IonPump ���ֵ
	double			dVacBak;
	double			dThreshold1;	// ��ֵ1
	double			dThreshold2;	// ��ֵ2
	int				nPort;			// COM�˿ں�
	int				nType;			// ��IPG(1)��IPC(2)������CCG(3)
	BOOL			bReady;			// �˿��Ƿ�������
	BOOL			bInInterlock;	// �Ƿ������ո�ѹ����
} CfgVAC_IP_CCG;



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// ��ǹ��Ŀ����տ��ư��ͨѶ

const	BYTE	byte_Head		= 0xF2;
const	BYTE	byte_Tail		= 0x2F;
const	BYTE	byte_LenSnd		= 0x05;
const	BYTE	byte_LenRec		= 0x06;

// 1. PC������տ��ư��ͨ��֡��ʽ
//	֡ͷByte1	��������Byte2	������Byte3		У��(XOR)Byte4		֡βByte5
//	F2			opcXXX			XX				Byte2 XOR Byte3		2F

// PC������տ��ư������
const	BYTE	byte_opcVent	= 0x01;		// oprand = 0x01������
const	BYTE	byte_opcPump	= 0x03;		// oprand = 0x03�������

const	BYTE	byte_opcV1		= 0x02;		// oprand = 0x01������V1��oprand = 0x02���ر�V1

const	BYTE	byte_opcStatus	= 0x11;		// oprand = 0x11����ȡ���״̬
const	BYTE	byte_opcIPG		= 0x21;		// oprand = 0x21����ȡIPGֵ
const	BYTE	byte_opcClr		= 0x91;		// oprand = 0x91�����ǹ��մ���



// 2. ��տ��ư��ϴ�����Ӧ֡��ʽ
//	֡ͷByte1	��������Byte2	����1 Byte3		����2 Byte4		У��(XOR)Byte5				֡βByte6
//	F2			opcXXX			XX				XX				Byte2 XOR Byte3 XOR Byte4	2F

// ��տ��ư����͵�����
//const	BYTE	byte_opcStatus	= 0x11;		// �������״̬�͸�����������״̬
											// ����1��0xXY
											//	X��	0 ��ʼ��״̬��1 ��Ʒ�Ҵ���״̬��2 �����״̬
											//		3 �����״̬��4 TMP����״̬��5 TMP���д���״̬
											//	Y��	0bMKQP
											//		M��1 ǹ��մ���״̬��0 ǹ�������״̬
											//		KQP ����
											//	����2��0b ABCD EFGH ��1Ϊ����0Ϊ�أ�
											//		A��B��������C��CCG��Դ��D��TMP��E��MP��F��Vvent2��G��Vvent1��H��V1

//const	BYTE	byte_opcIPG		= 0x21;		// ����1��0xXX������2��0xXX���ֱ��Ӧ16λADC��ֵ
//const	BYTE	byte_opcClr		= 0x91;		// ����1��0x00������2��0x00�������ǹ��մ���



// ����տ���ģ���յ�PC������opcVent��opcV1��opcPump��opcStatus�����ִ�в�Ӧ��opcStatus
// ����տ���ģ���յ�PC������opcIPG����ʱ��Ӧ��opcIPG
// ����տ���ģ���յ�PC������opcClr����ʱ�����ǹ��մ���Ӧ��opcClr



// 3. ��տ��ư��ϴ��ı���֡��ʽ
//	֡ͷByte1	��������Byte2	����1 Byte3	����2 Byte4		У��(XOR)Byte5				֡βByte6
//	F2			opcXXX			XX			XX				Byte2 XOR Byte3 XOR Byte4	2F

// ��տ��ư��ϴ��ı���֡����
const	BYTE	byte_opcWarning	= 0x92;		// ����1��0x92;
											// ����2��0x01 ǹ��մ��󱨾�; 0x00 TMP���б���
// ��λ����������PC����Ӧֵ



typedef struct tagVACstatus_Board{
	double	dPipg;

	BYTE	byteVent;		// 0x01��������0x03������
	BYTE	byteV1;			// 0x01��������0x02���ر�

	WORD	wStatus;
	BOOL	bV1;
	BOOL	bVvent1;
	BOOL	bVvent2;
	BOOL	bMP;
	BOOL	bTMP;
	BOOL	bCCG;
	BYTE	bX;
	BYTE	bY;
} StatusVAC_board;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#endif
