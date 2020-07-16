#ifndef __CommMC600_H
#define __CommMC600_H

#include <afxtempl.h>

#define WM_USER_MC600_UpdateValue	(WM_USER+98)

const	int nSpeedXY		= 960;
const	int	nSpeedInitXY	= 800;
const	int	nSpeedHomeXY	= 800;

// typedef struct
// {
// }KYKYCommMsg_Ver, *PKYKYCommMsg_Ver;

typedef enum _MC600_Param_Speed{
	Speed,			// �������ٶ�
	SpeedInit,		// ��������ٶ�
	SpeedAcc,		// ��������ٶ�
	SpeedHome		// �������ԭ���ٶ�
} MC600_Param_Speed;

typedef enum _MC600_Param_Home{
	Origin,			// �˶������ģʽ
	HomeMode,		// �˶�����㷽ʽ
	UserOrigin		// �˶��Ṥ��ԭ��
} MC600_Param_Home;

typedef enum _MC600_Param_Limit{
	LimitAble,		// �˶�������λ״̬
	LimitPositive,	// �˶��������������
	LimitNegative	// �˶��Ḻ���������
} MC600_Param_Limit;

typedef enum _MC600_Param_Sys{
	Unit,			// �˶���ʹ�õ�λ
	Style,			// ̨������
	WorkState,		// ̨�ӹ���״̬
	Pitch,			// ˿�ܵ���
	StepsRev,		// ÿת������������
	DriveRat,		// ������
	Distance		// ƽ��̨���г�
// 	Radius,			// ��դ�뾶
// 	EncoderStyle,	// ��դ������
// 	EncoderReso		// ��դ�߷ֱ���
} MC600_Param_Sys;

// PortOutput,	// ������IO��

typedef struct _MC600_Params_Sys{
	float	fPitch[4];		// ˿�ܵ���
	float	fStepsRev[4];	// ÿת������������
	float	fRat[4];		// ������
	float	fDistance[4];	// ƽ��̨���г�
} MC600_Params_Sys;

typedef struct _MC600_Params_Speed{
	float	fSpeed[4];		// �������ٶ�
	float	fSpeedInit[4];	// ��������ٶ�
	float	fSpeedAcc[4];	// ��������ٶ�
	float	fSpeedHome[4];	// �������ԭ���ٶ�
} MC600_Params_Speed;

typedef struct _MC600_Params_Pos{
	float	fSteps[4];		// ��ǰλ��
	float	fOrigin[4];		// �û�ԭ��λ��
} MC600_Params_Pos;

typedef struct _MC600_Params_Bl{	// ��϶����
	short	nDir[4];		// -1��ʾ������1��ʾ������
	int		nCount[4];		// ��϶������λpp
} MC600_Params_Bl;

struct structMC600Pos{
	CString	strName;		// ����
	float	fPos[4];		// λ��
};
typedef CTypedPtrList< CPtrList, structMC600Pos* > ListMC600Pos;

typedef struct _MC600_Params_ZRes{
	float	fZ0WD;			// Z���������Ӧ�Ĺ�������Z0wd
	float	fSafeWD;		// ��ȫ���
	float	fZsink;			// ���ε���̽ͷ��Ե���ﾵ��Z�³�
//	float	fZ16;			// Z����������ʼ��λ��λ��

	float	fZbr[2];		// �����棺br1ΪZ�����λ��������ʼ��λ��λ��
							//			Zbr1 = Z16 = Z0wd -H -Zsink
							//			Zbr0 = Z16 +H = Z0wd -Zsink
	float	fCali[3];		// X/Y/Z �������Ʊ궨λ�ã�����X�궨=-20.2��Y�궨=-30.0��
							//							Z�궨 = Z0wd -safeWD -H
	float	fLimitPos[3];	// X/Y/Z ������
	float	fLimitNeg[3];	// X/Y/Z ������

	float	fRt;			// ̽ͷ�뾶��10.0
	float	fRyp;			// ��Ʒ�뾶��[8,50)���û������룬ȱʡΪ16
	float	fRx0;			// 24.5
	float	fRy0;			// 16.0

	float	fH;				// ��Ʒ�߶�H���û�[5-30)��������Ա[3,30)��ȱʡΪ16
} MC600_Params_ZRes;
#endif
