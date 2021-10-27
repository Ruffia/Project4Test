#pragma once
#include "FaultCommandBase.h"

//DD���������ź�
class DD_Motor_Overcurrent : public CFaultCommandBase
{
public:
	DD_Motor_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//PA������
class PA_Overcurrent : public CFaultCommandBase
{
public:
	PA_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};

//��е������������
class TA_Drive_Overcurrent : public CFaultCommandBase
{
public:
	TA_Drive_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//Loadlock����������
class Loadlock_Drive_Overcurrent : public CFaultCommandBase
{
public:
	Loadlock_Drive_Overcurrent();

protected:
	virtual void _BuildAddress2Send();
};


//��е��VAC�쳣
class TA_VAC_Err : public CFaultCommandBase
{
public:
	TA_VAC_Err();

protected:
	virtual void _BuildAddress2Send();
};


//PLCϵͳ����
class PLC_System_Err : public CFaultCommandBase
{
public:
	PLC_System_Err();

protected:
	virtual void _BuildAddress2Send();
};


//X����������������е�֣�
class X_Drive_Err : public CFaultCommandBase
{
public:
	X_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//Z����������������е�֣�
class Z_Drive_Err : public CFaultCommandBase
{
public:
	Z_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//R����������������е�֣�
class R_Drive_Err : public CFaultCommandBase
{
public:
	R_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//���ͻ���������������Loadlock��
class CV1_Drive_Err : public CFaultCommandBase
{
public:
	CV1_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


//��ͷ����������������Loadlock��
class CV2_Drive_Err : public CFaultCommandBase
{
public:
	CV2_Drive_Err();

protected:
	virtual void _BuildAddress2Send();
};


