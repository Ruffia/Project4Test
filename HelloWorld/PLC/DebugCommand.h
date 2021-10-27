#pragma once
#include "DebugCommandBase.h"

//X取片位置（进入cassette）
class X_WaferTaking_Positin : public CDebugCommandBase
{
public:
	X_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//Z取片位置（进入cassette）
class Z_WaferTaking_Positin : public CDebugCommandBase
{
public:
	Z_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//R取片位置（进入cassette）
class R_WaferTaking_Positin : public CDebugCommandBase
{
public:
	R_WaferTaking_Positin();

protected:
	virtual void _BuildAddress2Send();
};


//R到PA位置
class R_toPA_Position : public CDebugCommandBase
{
public:
	R_toPA_Position();

protected:
	virtual void _BuildAddress2Send();
};


//Z到PA位置
class Z_ToPA_Positon : public CDebugCommandBase
{
public:
	Z_ToPA_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//X到PA位置
class X_ToPA_Positon : public CDebugCommandBase
{
public:
	X_ToPA_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//Z到Loadlock位置
class Z_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	Z_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//R到Loadlock位置
class R_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	R_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};


//X到Loadlock位置
class X_ToLoadlock_Positon : public CDebugCommandBase
{
public:
	X_ToLoadlock_Positon();

protected:
	virtual void _BuildAddress2Send();
};
