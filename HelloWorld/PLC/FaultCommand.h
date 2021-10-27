#pragma once
#include "FaultCommandBase.h"

//DD马达过电流信号
class DD_Motor_Overcurrent : public CFaultCommandBase
{
public:
	DD_Motor_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//PA过电流
class PA_Overcurrent : public CFaultCommandBase
{
public:
	PA_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};

//机械手驱动过电流
class TA_Drive_Overcurrent : public CFaultCommandBase
{
public:
	TA_Drive_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//Loadlock驱动过电流
class Loadlock_Drive_Overcurrent : public CFaultCommandBase
{
public:
	Loadlock_Drive_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//机械手VAC异常
class TA_VAC_Err : public CFaultCommandBase
{
public:
	TA_VAC_Err();

protected:
	virtual void _BuildAddress2Send();
};


//PLC系统故障
class PLC_System_Err : public CFaultCommandBase
{
public:
	PLC_System_Err();

protected:
	virtual void _BuildAddress2Send();
};


//X轴驱动器报警（机械手）
class X_Drive_Err : public CFaultCommandBase
{
public:
	X_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//Z轴驱动器报警（机械手）
class Z_Drive_Err : public CFaultCommandBase
{
public:
	Z_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//R轴驱动器报警（机械手）
class R_Drive_Err : public CFaultCommandBase
{
public:
	R_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//传送机构驱动器报警（Loadlock）
class CV1_Drive_Err : public CFaultCommandBase
{
public:
	CV1_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//舌头机构驱动器报警（Loadlock）
class CV2_Drive_Err : public CFaultCommandBase
{
public:
	CV2_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


