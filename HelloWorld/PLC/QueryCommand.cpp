#include "stdafx.h"
#include "QueryCommand.h"
#include "Factory.h"
#include <string>

IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_Initial_finished,std::string,"SendWafer_Initial_finished")
SendWafer_Initial_finished::SendWafer_Initial_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.00");
}


void SendWafer_Initial_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_Cassette2PA_finished,std::string,"SendWafer_Cassette2PA_finished")
SendWafer_Cassette2PA_finished::SendWafer_Cassette2PA_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.01");
}


void SendWafer_Cassette2PA_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x01;
}


IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_PA_2Loadlock_Ready,std::string,"SendWafer_PA_2Loadlock_Ready")
SendWafer_PA_2Loadlock_Ready::SendWafer_PA_2Loadlock_Ready()
{
	strcpy_s(m_szMapAddress,"CIO5100.02");
}


void SendWafer_PA_2Loadlock_Ready::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x02;
}


IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_G2Open_In_finished,std::string,"SendWafer_G2Open_In_finished")
SendWafer_G2Open_In_finished::SendWafer_G2Open_In_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.03");
}

void SendWafer_G2Open_In_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_WaferInSEM_IN_finished,std::string,"SendWafer_WaferInSEM_IN_finished")
SendWafer_WaferInSEM_IN_finished::SendWafer_WaferInSEM_IN_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.04");
}

void SendWafer_WaferInSEM_IN_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x04;
}


IMPLEMENT_FACTORY(CQueryCommandBase,SendWafer_WaferReleaseFromStage,std::string,"SendWafer_WaferReleaseFromStage")
SendWafer_WaferReleaseFromStage::SendWafer_WaferReleaseFromStage()
{
	strcpy_s(m_szMapAddress,"CIO5100.05");
}

void SendWafer_WaferReleaseFromStage::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x05;
}


IMPLEMENT_FACTORY(CQueryCommandBase,RemoveWafer_CV2SEM_finished,std::string,"RemoveWafer_CV2SEM_finished")
RemoveWafer_CV2SEM_finished::RemoveWafer_CV2SEM_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.06");
}

void RemoveWafer_CV2SEM_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x06;
}


IMPLEMENT_FACTORY(CQueryCommandBase,RemoveWafer_ReturnWafer2LoadLock_finished,std::string,"RemoveWafer_ReturnWafer2LoadLock_finished")
RemoveWafer_ReturnWafer2LoadLock_finished::RemoveWafer_ReturnWafer2LoadLock_finished()
{
	strcpy_s(m_szMapAddress,"CIO5100.07");
}


void RemoveWafer_ReturnWafer2LoadLock_finished::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x07;
}


IMPLEMENT_FACTORY(CQueryCommandBase,RemoveWafer_WaferBack2Cassette,std::string,"RemoveWafer_WaferBack2Cassette")
RemoveWafer_WaferBack2Cassette::RemoveWafer_WaferBack2Cassette()
{
	strcpy_s(m_szMapAddress,"CIO5100.08");
}


void RemoveWafer_WaferBack2Cassette::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0xEC;
	m_pCommand[15] = 0x08;
}