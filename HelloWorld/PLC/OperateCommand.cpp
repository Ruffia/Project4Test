#include "stdafx.h"
#include "OperateCommand.h"
#include "Factory.h"
#include <string>

IMPLEMENT_FACTORY(IPLCCommand,SendWafer_Initial,std::string,"SendWafer_Initial")
SendWafer_Initial::SendWafer_Initial()
{
	strcpy_s(m_szMapAddress,"CIO5000.00");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_Initial_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void SendWafer_Initial::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,SendWafer_PAReady,std::string,"SendWafer_PAReady")
SendWafer_PAReady::SendWafer_PAReady()
{
	strcpy_s(m_szMapAddress,"CIO5000.01");
}

void SendWafer_PAReady::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x01;
}

IMPLEMENT_FACTORY(IPLCCommand,SendWafer_Cassette2PA,std::string,"SendWafer_Cassette2PA")
SendWafer_Cassette2PA::SendWafer_Cassette2PA()
{
	strcpy_s(m_szMapAddress,"CIO5000.02");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_Cassette2PA_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void SendWafer_Cassette2PA::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x02;
}

IMPLEMENT_FACTORY(IPLCCommand,SendWafer_LayWaferOnPA,std::string,"SendWafer_LayWaferOnPA")
SendWafer_LayWaferOnPA::SendWafer_LayWaferOnPA()
{
	strcpy_s(m_szMapAddress,"CIO5000.03");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_PA_2Loadlock_Ready");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void SendWafer_LayWaferOnPA::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(IPLCCommand,SendWafer_G2Open_In,std::string,"SendWafer_G2Open_In")
SendWafer_G2Open_In::SendWafer_G2Open_In()
{
	strcpy_s(m_szMapAddress,"CIO5000.04");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_G2Open_In_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}

}

void SendWafer_G2Open_In::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x04;
}


IMPLEMENT_FACTORY(IPLCCommand,SendWafer_G1Open_In,std::string,"SendWafer_G1Open_In")
SendWafer_G1Open_In::SendWafer_G1Open_In()
{
	strcpy_s(m_szMapAddress,"CIO5000.05");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_WaferInSEM_IN_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void SendWafer_G1Open_In::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x05;
}


IMPLEMENT_FACTORY(IPLCCommand,SendWafer_StageLiftWafer,std::string,"SendWafer_StageLiftWafer")
SendWafer_StageLiftWafer::SendWafer_StageLiftWafer()
{
	strcpy_s(m_szMapAddress,"CIO5000.06");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("SendWafer_WaferReleaseFromStage");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void SendWafer_StageLiftWafer::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x06;
}


IMPLEMENT_FACTORY(IPLCCommand,RemoveWafer_CV2SEM,std::string,"RemoveWafer_CV2SEM")
RemoveWafer_CV2SEM::RemoveWafer_CV2SEM()
{
	strcpy_s(m_szMapAddress,"CIO5000.07");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("RemoveWafer_CV2SEM_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}


void RemoveWafer_CV2SEM::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x07;
}



IMPLEMENT_FACTORY(IPLCCommand,RemoveWafer_ReturnWafer2LoadLock,std::string,"RemoveWafer_ReturnWafer2LoadLock")
RemoveWafer_ReturnWafer2LoadLock::RemoveWafer_ReturnWafer2LoadLock()
{
	strcpy_s(m_szMapAddress,"CIO5000.08");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("RemoveWafer_ReturnWafer2LoadLock_finished");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void RemoveWafer_ReturnWafer2LoadLock::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x08;
}


IMPLEMENT_FACTORY(IPLCCommand,RemoveWafer_G2Open,std::string,"RemoveWafer_G2Open")
RemoveWafer_G2Open::RemoveWafer_G2Open()
{
	strcpy_s(m_szMapAddress,"CIO5000.09");
	m_pQueryCommand = Factory<CQueryCommandBase,std::string>::Instance().BuildProduct("RemoveWafer_WaferBack2Cassette");
	if(m_pQueryCommand)
	{
		m_pQueryCommand->BuildCommand();
	}
}

void RemoveWafer_G2Open::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x09;
}