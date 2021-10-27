#include "stdafx.h"
#include "BaseCommand.h"

IPLCCommand::IPLCCommand():
	m_pCommand(NULL),m_pResp(NULL)
{
	memset(m_szMapAddress,16,0);
	memset(m_szCommand,128,0);
}


IPLCCommand::~IPLCCommand()
{
	if(m_pCommand)
	{
		delete m_pCommand;
		m_pCommand = NULL;
	}

	if (m_pResp)
	{
		delete m_pResp;
		m_pResp = NULL;
	}
}


void IPLCCommand::BuildCommand()
{
	_Initialize();
	_BuildFixed1();
	_BuildIP1();
	_BuildFixed2();
	_BuildIP2();
	_BuildFixed3();
	_BuildOperateData();
	_BuildStorageCode();
	_BuildAddress2Send();
	_BuildLength();
	_BuildData();
}


char* IPLCCommand::GetCommand()
{
	memset(m_szCommand,0,128);
	//strcat_s(m_szCommand,m_szMapAddress);
	//strcat_s(m_szCommand,": ");

	int nLength = (int)_msize(m_pCommand);
	for (int i = 0; i < nLength;i++)
	{
		char sz[8] = {0};
		if (nLength - 1 == i)
		{
			sprintf_s(sz,"%02X",m_pCommand[i]);
		}
		else
		{
			sprintf_s(sz,"%02X ",m_pCommand[i]);
		}
		
		strcat_s(m_szCommand,sz);
	}

	return m_szCommand;
}

void IPLCCommand::_BuildFixed1()
{
	m_pCommand[0] = 0x80;
	m_pCommand[1] = 0x00;
	m_pCommand[2] = 0x02;
	m_pCommand[3] = 0x00;
}


void IPLCCommand::_BuildIP1()
{
	m_pCommand[4] = 0x01;
}


void IPLCCommand::_BuildFixed2()
{
	m_pCommand[5] = 0x00;
	m_pCommand[6] = 0x00;
}


void IPLCCommand::_BuildIP2()
{
	m_pCommand[7] = 0x0A;
}


void IPLCCommand::_BuildFixed3()
{
	m_pCommand[8] = 0x00;
	m_pCommand[9] = 0x00;
}
