#ifndef __CommFunctions_H
#define __CommFunctions_H

//发送命令字定义
#define	KYKYComm_TimerID_Listen		200
#define	KYKYComm_TimerID_Receive	201
#define	KYKYComm_TimerID_Send		202

#define	KYKYComm_IMAGEDATA			2000	//请求图像数据


#define	KYKYComm_CMD_Sys_Password			0x01
#define KYKYComm_CMD_Sys_Connect_Success	0x02
#define KYKYComm_CMD_Sys_Disconnect			0x03
#define KYKYComm_CMD_Sys_ErrInfo			0x04
#define KYKYComm_CMD_Sys_GetVersion			0x05
#define KYKYComm_CMD_Sys_GetSEMType			0x06

#define KYKYComm_CMD_Image_Sync				0x11
#define KYKYComm_CMD_Image_Stop				0x12
#define KYKYComm_CMD_Image_Snap				0x13
#define KYKYComm_CMD_Image_Save				0x14

#define KYKYComm_CMD_ScanCtrl_Freeze		0x21
#define KYKYComm_CMD_ScanCtrl_Normal		0x22
#define KYKYComm_CMD_ScanCtrl_ActiveArea	0x23
#define KYKYComm_CMD_ScanCtrl_Line_HORZ		0x24
#define KYKYComm_CMD_ScanCtrl_Line_VERT		0x25
#define KYKYComm_CMD_ScanCtrl_Spot			0x26
#define KYKYComm_CMD_ScanCtrl_Sync			0x27

#define KYKYComm_CMD_ScanCtrl_Speed1		0x31
#define KYKYComm_CMD_ScanCtrl_Speed2		0x32
#define KYKYComm_CMD_ScanCtrl_Speed3		0x33
#define KYKYComm_CMD_ScanCtrl_Speed4		0x34

#define KYKYComm_CMD_ScanCtrl_Reso			0x35
#define KYKYComm_CMD_ScanCtrl_Reso1			0x36
#define KYKYComm_CMD_ScanCtrl_Reso2			0x37
#define KYKYComm_CMD_ScanCtrl_Reso3			0x38
#define KYKYComm_CMD_ScanCtrl_Reso4			0x39

#define KYKYComm_CMD_Get_Magnification		0x41
#define KYKYComm_CMD_Get_WorkDistance		0x42
#define KYKYComm_CMD_Get_ScanRotAngleInit	0x43
#define KYKYComm_CMD_Get_ScanRotAngle		0x44
#define KYKYComm_CMD_Get_Stigmators			0x45
#define KYKYComm_CMD_Get_Brightness			0x46
#define KYKYComm_CMD_Get_Contrast			0x47
#define KYKYComm_CMD_Get_Brightness2		0x48

#define KYKYComm_CMD_Set_Magnification		0x49
#define KYKYComm_CMD_Set_ScanRotAngle		0x4A
#define KYKYComm_CMD_Set_Stigmators			0x4B
#define KYKYComm_CMD_Set_Brightness			0x4C
#define KYKYComm_CMD_Set_Contrast			0x4D
#define KYKYComm_CMD_Set_Brightness2		0x4E

#define KYKYComm_CMD_Get_HighVoltageType	0x50
#define KYKYComm_CMD_Get_HighVoltage		0x51
#define KYKYComm_CMD_Get_Fila				0x52
#define KYKYComm_CMD_Get_BeamCurrent		0x53
#define KYKYComm_CMD_Set_HighVoltage		0x54
#define KYKYComm_CMD_Set_Fila				0x55
#define KYKYComm_CMD_Set_BeamCurrent		0x56
#define KYKYComm_CMD_Get_Bias				0x57
#define KYKYComm_CMD_Set_Bias				0x58
#define KYKYComm_CMD_Get_EMI				0x59

#define KYKYComm_CMD_Get_VacStatus			0x5E
#define KYKYComm_CMD_Get_GunStatus			0x5F

#define KYKYComm_CMD_Stage_GetStatus		0x61
#define KYKYComm_CMD_Stage_GetGrating		0x62
#define KYKYComm_CMD_Stage_GetRange			0x63
#define KYKYComm_CMD_Stage_GetPosXY			0x64
#define KYKYComm_CMD_Stage_SetPosXY			0x65
#define KYKYComm_CMD_Stage_Stop				0x66
#define KYKYComm_CMD_Stage_GetRange5		0x67
#define KYKYComm_CMD_Stage_GetPos5			0x68
#define KYKYComm_CMD_Stage_SetPos5			0x69
#define KYKYComm_CMD_Stage_GoHome			0x6A

#define KYKYComm_CMD_Func_AutoBC			0x71

/*
#define WM_USER_KYKYComm_StartListen			WM_USER+501
#define WM_USER_KYKYComm_Error_Bind				WM_USER+502
#define WM_USER_KYKYComm_Error_Listen			WM_USER+503
*/
#define WM_USER_KYKYComm_Thread_Connect			WM_USER+511
#define WM_USER_KYKYComm_Connect_Status			WM_USER+512
#define WM_USER_KYKYComm_Timeout				WM_USER+513
#define WM_USER_KYKYComm_Thread_Read			WM_USER+514
#define WM_USER_KYKYComm_Thread_Send			WM_USER+515
#define WM_USER_KYKYComm_Thread_Send_Connect	WM_USER+516
#define WM_USER_KYKYComm_Recv					WM_USER+517

#define WM_USER_KYKYComm_ClientThreadSend_Command	WM_USER+521
#define WM_USER_KYKYComm_ClientThreadSend_Param	WM_USER+522
#define WM_USER_KYKYComm_Thread_MCICard_GetRect  WM_USER+610

//#define nRowLen  8
#define KYKYComm_SnapMode				1
#define KYKYComm_SimulScanMode			2
#define KYKYComm_ListenPort1			3000
#define KYKYComm_ListenPort2			3500

#define KYKYComm_IMGSIZE				(2048*16)	//1024*768 +1    2048*1536
#define KYKYComm_MALLOC_SIZE			20			//用于存储接收到的图像数据的内存块的数量，以一次接收图像数据块为单位

const	UINT KYKYComm_Remote_Timer		= 50;

typedef struct
{
	BYTE	bHead;
	BYTE	bCommand;
	WORD	versionNum;
}KYKYCommMsg_Ver, *PKYKYCommMsg_Ver;

typedef struct  
{
	BYTE bHead;
	BYTE bCommand;
	int  nSendData;
}KYKYCommMsg_SendDataS1i, *PKYKYCommMsg_SendDataS1i;

typedef struct
{
	BYTE	bHead;
	BYTE	bCommand;
	CSize	szSize;
}KYKYCommMsg_SendDataS2i, *PKYKYCommMsg_SendDataS2i;

typedef struct
{
	BYTE	bHead;
	BYTE	bCommand;
	double	dValue;
}KYKYCommMsg_SendDataS1f, *PKYKYCommMsg_SendDataS1f;

typedef struct  
{
	float	fValue1;
	float	fValue2;
}KYKYCommMsg_Data2f;

typedef struct  
{
	float	fValue1;
	float	fValue2;
	float	fValue3;
	float	fValue4;
	float	fValue5;
}KYKYCommMsg_Data5f;

typedef struct
{
	BYTE	bHead;
	BYTE	bCommand;
	KYKYCommMsg_Data5f	Values;
}KYKYCommMsg_SendDataS5f, *PKYKYCommMsg_SendDataS5f;

typedef struct
{
	CRect   rcDest;
	BYTE	bImageBuff[KYKYComm_IMGSIZE];
}KYKYCommMsg_ImgData, *PKYKYCommMsg_ImgData;

typedef struct  
{
	BYTE	bHead;
	BYTE	bCommand;
	KYKYCommMsg_ImgData	msgImgData;
}KYKYCommMsg_Image;

///////////////////////////////////////
typedef struct  
{
	BYTE	bHead1;
	BYTE	bHead2;
	BYTE	bCommand;
	int		nValue;
}KYKYCommMsg_SendDataC1i, *PKYKYCommMsg_SendDataC1i;	// Client send data: 1 int data

typedef struct
{
	BYTE	bHead1;
	BYTE	bHead2;
	BYTE	bCommand;
	CSize	szSize;
}KYKYCommMsg_SendDataC2i, *PKYKYCommMsg_SendDataC2i;	// Client send data: 2 int data

typedef struct
{
	BYTE	bHead1;
	BYTE	bHead2;
	BYTE	bCommand;
	float	fValue;
}KYKYCommMsg_SendDataC1f, *PKYKYCommMsg_SendDataC1f;	// Client send data: 1 float data

typedef struct
{
	BYTE	bHead1;
	BYTE	bHead2;
	BYTE	bCommand;
	float	fValue1;
	float	fValue2;
}KYKYCommMsg_SendDataC2f, *PKYKYCommMsg_SendDataC2f;	// Client send data: 2 float data

typedef struct
{
	BYTE	bHead1;
	BYTE	bHead2;
	BYTE	bCommand;
	KYKYCommMsg_Data5f Values;
}KYKYCommMsg_SendDataC5f, *PKYKYCommMsg_SendDataC5f;	// Client send data: 5 float data
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//发送命令字定义
#define  TimerID_Listen			0
#define  TimerID_Receive		1
#define  TimerID_Send			2

#define	IMAGEDATA				2000				//请求图像数据


#define CMD_PASSWORD			0X01
#define CMD_CONNECT_SECCESS		0X02
#define CMD_ERRINFO				0X03
#define CMD_QUERY_VERSION		0X04
#define CMD_SNAP				0X05
#define CMD_SIMULIMAGE			0X06
#define CMD_SAVE				0X07
#define CMD_DISCONNECT			0X08
#define CMD_RESOLUTION			0X09
#define CMD_SIMULSCAN			0x0A
#define CMD_NORMALSCAN			0x0B
#define CMD_STOPSIMULIMAGE		0x0C
#define CMD_FREEZESCAN			0X0D

#define CMD_SCAN_SPEED1			0X0E
#define CMD_SCAN_SPEED2			0X0F
#define CMD_SCAN_SPEED3			0X10
#define CMD_SCAN_SPEED4			0X11

#define CMD_IMAGE_RESOLUTION1	0X12
#define CMD_IMAGE_RESOLUTION2	0X13
#define CMD_IMAGE_RESOLUTION3	0X14
#define CMD_IMAGE_RESOLUTION4	0X15

#define CMD_MAGNIFICATION		0X16
#define CMD_SCANROT_ANGLE		0X17



#define WM_THREAD_READ			WM_USER+500
#define WM_RECV					WM_USER+501
#define WM_SEND_CONNECT_THREAD	WM_USER+502  
#define WM_THREAD_SEND			WM_USER+503 
#define WM_CONNECT_STATUS		WM_USER+504
#define WM_OUTTIME				WM_USER+505
#define WM_BINDERROR			WM_USER+506
#define WM_LISTENERROR			WM_USER+507
#define WM_STARTLISTEN			WM_USER+508

#define WP_RECV					100
#define WP_SEND					101

//#define nRowLen  8
#define nSnapMode				1
#define nSimulScanMode			2
#define nPort1					3000
#define nPort2					3500

#define IMGSIZE					(2048*16)	//1024*768 +1    2048*1536
#define MALLOC_SIZE				20			//用于存储接收到的图像数据的内存块的数量，以一次接收图像数据块为单位

const	UINT nRemote_Timer		= 50;

/*
typedef struct 
{
	CSize szReso;
}MSGIMAGESIZE, *PMSGIMAGESIZE;

typedef struct  
{
	BYTE bHead;
	BYTE bCommand;
	int  nSendVal;
}MSGSENDINT;

typedef struct
{
	BYTE bHead;
	BYTE bCommand;
	MSGIMAGESIZE msgSize;
}MSGRESOLUTION;

typedef struct
{
	CRect   rcDest;
	BYTE	bImageBuff[IMGSIZE];
}MSGIMAGEDATA, *PMSGIMAGEDATA;

typedef struct  
{
	BYTE	bHead;
	BYTE	bCommand;
	MSGIMAGEDATA	msgData;
}MSGIMAGE;

typedef struct
{
	BYTE	bHead;
	BYTE	bCommand;
	WORD	versionNum;
}MSGVERSION, *PMSGVERSION;

/*
typedef struct
{
	int  iCommand;
	CRect rcDest;
	BYTE bImageBuff[IMGSIZE];
}MSGIMAGEDATA;
*/

#endif
