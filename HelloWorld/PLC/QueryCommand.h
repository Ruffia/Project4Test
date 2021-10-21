#include "QueryCommandBase.h"

class SendWafer_Initial_finished : public CQueryCommandBase
{
public:
	SendWafer_Initial_finished();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_Cassette2PA_finished : public CQueryCommandBase
{
public:
	SendWafer_Cassette2PA_finished();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_PA_2Loadlock_Ready : public CQueryCommandBase
{
public:
	SendWafer_PA_2Loadlock_Ready();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_G2Open_In_finished : public CQueryCommandBase
{
public:
	SendWafer_G2Open_In_finished();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_WaferInSEM_IN_finished : public CQueryCommandBase
{
public:
	SendWafer_WaferInSEM_IN_finished();

protected:
	virtual void _BuildAddress2Send();
};


class SendWafer_WaferReleaseFromStage : public CQueryCommandBase
{
public:
	SendWafer_WaferReleaseFromStage();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_CV2SEM_finished : public CQueryCommandBase
{
public:
	RemoveWafer_CV2SEM_finished();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_ReturnWafer2LoadLock_finished : public CQueryCommandBase
{
public:
	RemoveWafer_ReturnWafer2LoadLock_finished();

protected:
	virtual void _BuildAddress2Send();
};


class RemoveWafer_WaferBack2Cassette : public CQueryCommandBase
{
public:
	RemoveWafer_WaferBack2Cassette();

protected:
	virtual void _BuildAddress2Send();
};
