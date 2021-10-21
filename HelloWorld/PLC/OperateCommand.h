#include "OperateCommandBase.h"

class SendWafer_Initial : public COperateCommandBase
{
public:
	SendWafer_Initial();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_PAReady : public COperateCommandBase
{
public:
	SendWafer_PAReady();

protected:
	virtual void _BuildAddress2Send();
};

class SendWafer_Cassette2PA : public COperateCommandBase
{
public:
	SendWafer_Cassette2PA();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_LayWaferOnPA : public COperateCommandBase
{
public:
	SendWafer_LayWaferOnPA();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_G2Open_In : public COperateCommandBase
{
public:
	SendWafer_G2Open_In();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_G1Open_In : public COperateCommandBase
{
public:
	SendWafer_G1Open_In();


protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_StageLiftWafer : public COperateCommandBase
{
public:
	SendWafer_StageLiftWafer();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_CV2SEM : public COperateCommandBase
{
public:
	RemoveWafer_CV2SEM();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_ReturnWafer2LoadLock : public COperateCommandBase
{
public:
	RemoveWafer_ReturnWafer2LoadLock();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_G2Open : public COperateCommandBase
{
public:
	RemoveWafer_G2Open();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_1 : public COperateCommandBase
{
public:
	TakingWafer_1();

protected:
	virtual void _BuildAddress2Send();
};

class TakingWafer_2 : public COperateCommandBase
{
public:
	TakingWafer_2();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_3 : public COperateCommandBase
{
public:
	TakingWafer_3();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_4 : public COperateCommandBase
{
public:
	TakingWafer_4();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_5 : public COperateCommandBase
{
public:
	TakingWafer_5();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_6 : public COperateCommandBase
{
public:
	TakingWafer_6();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_7 : public COperateCommandBase
{
public:
	TakingWafer_7();

protected:
	virtual void _BuildAddress2Send();
};

class TakingWafer_8 : public COperateCommandBase
{
public:
	TakingWafer_8();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_9 : public COperateCommandBase
{
public:
	TakingWafer_9();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_10 : public COperateCommandBase
{
public:
	TakingWafer_10();

protected:
	virtual void _BuildAddress2Send();
};

class TakingWafer_11 : public COperateCommandBase
{
public:
	TakingWafer_11();

protected:
	virtual void _BuildAddress2Send();
};


class TakingWafer_12 : public COperateCommandBase
{
public:
	TakingWafer_12();

protected:
	virtual void _BuildAddress2Send();
};


class Motor_Power_On : public COperateCommandBase
{
public:
	Motor_Power_On();

protected:
	virtual void _BuildAddress2Send();
};


class Motor_Power_Off : public COperateCommandBase
{
public:
	Motor_Power_Off();

protected:
	virtual void _BuildAddress2Send();
};


class Motor_Enable : public COperateCommandBase
{
public:
	Motor_Enable();

protected:
	virtual void _BuildAddress2Send();
};


class Motor_RetureZero : public COperateCommandBase
{
public:
	Motor_RetureZero();

protected:
	virtual void _BuildAddress2Send();
};


class Motor_Stop : public COperateCommandBase
{
public:
	Motor_Stop();

protected:
	virtual void _BuildAddress2Send();
};


class Position_parameter_Req : public COperateCommandBase
{
public:
	Position_parameter_Req();

protected:
	virtual void _BuildAddress2Send();
};