
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
	int				nPortIPG;		// IPG COM端口号
	int				nPortIPC;		// IPC COM端口号
	int				nPortCCG;		// CCG COM端口号
	BOOL			bIPGready;
	BOOL			bIPCready;
	BOOL			bCCGready;
	double			dVacIPG;		// IPG真空值
	double			dVacIPC;
	double			dVacCCG;
} CfgVAC_CCGIPG;

typedef struct tagVACcfg_IP_CCG{
	double			dVac;			// IonPump 真空值
	double			dVacBak;
	double			dThreshold1;	// 阈值1
	double			dThreshold2;	// 阈值2
	int				nPort;			// COM端口号
	int				nType;			// 是IPG(1)、IPC(2)，还是CCG(3)
	BOOL			bReady;			// 端口是否工作正常
	BOOL			bInInterlock;	// 是否参与真空高压联锁
} CfgVAC_IP_CCG;



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// 场枪项目与真空控制板的通讯

const	BYTE	byte_Head		= 0xF2;
const	BYTE	byte_Tail		= 0x2F;
const	BYTE	byte_LenSnd		= 0x05;
const	BYTE	byte_LenRec		= 0x06;

// 1. PC下送真空控制板的通信帧格式
//	帧头Byte1	命令名称Byte2	操作数Byte3		校验(XOR)Byte4		帧尾Byte5
//	F2			opcXXX			XX				Byte2 XOR Byte3		2F

// PC下送真空控制板的命令
const	BYTE	byte_opcVent	= 0x01;		// oprand = 0x01：放气
const	BYTE	byte_opcPump	= 0x03;		// oprand = 0x03：抽真空

const	BYTE	byte_opcV1		= 0x02;		// oprand = 0x01：开启V1；oprand = 0x02：关闭V1

const	BYTE	byte_opcStatus	= 0x11;		// oprand = 0x11：获取真空状态
const	BYTE	byte_opcIPG		= 0x21;		// oprand = 0x21：获取IPG值
const	BYTE	byte_opcClr		= 0x91;		// oprand = 0x91：清除枪真空错误



// 2. 真空控制板上传的响应帧格式
//	帧头Byte1	命令名称Byte2	参数1 Byte3		参数2 Byte4		校验(XOR)Byte5				帧尾Byte6
//	F2			opcXXX			XX				XX				Byte2 XOR Byte3 XOR Byte4	2F

// 真空控制板上送的命令
//const	BYTE	byte_opcStatus	= 0x11;		// 返回真空状态和各个开关量的状态
											// 参数1：0xXY
											//	X：	0 初始化状态；1 样品室大气状态；2 抽真空状态
											//		3 粗真空状态；4 TMP运行状态；5 TMP运行错误状态
											//	Y：	0bMKQP
											//		M：1 枪真空错误状态；0 枪真空正常状态
											//		KQP 保留
											//	参数2：0b ABCD EFGH （1为开，0为关）
											//		A、B：保留；C：CCG电源；D：TMP；E：MP；F：Vvent2；G：Vvent1；H：V1

//const	BYTE	byte_opcIPG		= 0x21;		// 参数1：0xXX；参数2：0xXX；分别对应16位ADC数值
//const	BYTE	byte_opcClr		= 0x91;		// 参数1：0x00；参数2：0x00；已清除枪真空错误



// 当真空控制模块收到PC发出的opcVent、opcV1、opcPump、opcStatus命令后，执行并应答opcStatus
// 当真空控制模块收到PC发出的opcIPG命令时，应答opcIPG
// 当真空控制模块收到PC发出的opcClr命令时，清除枪真空错误并应答opcClr



// 3. 真空控制板上传的报警帧格式
//	帧头Byte1	命令名称Byte2	参数1 Byte3	参数2 Byte4		校验(XOR)Byte5				帧尾Byte6
//	F2			opcXXX			XX			XX				Byte2 XOR Byte3 XOR Byte4	2F

// 真空控制板上传的报警帧命令
const	BYTE	byte_opcWarning	= 0x92;		// 参数1：0x92;
											// 参数2：0x01 枪真空错误报警; 0x00 TMP运行报警
// 下位机报警命令PC无响应值



typedef struct tagVACstatus_Board{
	double	dPipg;

	BYTE	byteVent;		// 0x01：放气；0x03：抽气
	BYTE	byteV1;			// 0x01：开启；0x02：关闭

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
