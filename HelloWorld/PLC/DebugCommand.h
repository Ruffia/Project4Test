#pragma once
#include "DebugCommandBase.h"

//XȡƬλ�ã�����cassette��
class X_WaferTaking_Positin : public CDebugCommandBase
{
public:
	X_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//ZȡƬλ�ã�����cassette��
class Z_WaferTaking_Positin : public CDebugCommandBase
{
public:
	Z_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//RȡƬλ�ã�����cassette��
class R_WaferTaking_Positin : public CDebugCommandBase
{
public:
	R_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//R��PAλ��
class R_toPA_Position : public CDebugCommandBase
{
public:
	R_toPA_Position();

protected:
	virtual void _BuildAddress2Send();
};


//Z��PAλ��
class Z_ToPA_Positon : public CDebugCommandBase
{
public:
	Z_ToPA_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//X��PAλ��
class X_ToPA_Positon : public CDebugCommandBase
{
public:
	X_ToPA_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//Z��Loadlockλ��
class Z_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	Z_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//R��Loadlockλ��
class R_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	R_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//X��Loadlockλ��
class X_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	X_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};
