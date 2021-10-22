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