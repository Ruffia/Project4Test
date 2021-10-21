#include "stdafx.h"
#include "DebugCommand.h"
#include "Factory.h"
#include <string>

IMPLEMENT_FACTORY(IPLCCommand,X_WaferTaking_Positin,std::string,"X_WaferTaking_Positin")
X_WaferTaking_Positin::X_WaferTaking_Positin()
{
	strcpy_s(m_szMapAddress,"DM10");
}

void X_WaferTaking_Positin::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x0A;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,Z_WaferTaking_Positin,std::string,"Z_WaferTaking_Positin")
Z_WaferTaking_Positin::Z_WaferTaking_Positin()
{
	strcpy_s(m_szMapAddress,"DM30");
}


void Z_WaferTaking_Positin::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x1E;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,R_WaferTaking_Positin,std::string,"R_WaferTaking_Positin")
R_WaferTaking_Positin::R_WaferTaking_Positin()
{
	strcpy_s(m_szMapAddress,"DM50");
}

void R_WaferTaking_Positin::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x32;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,R_toPA_Position,std::string,"R_toPA_Position")
R_toPA_Position::R_toPA_Position()
{
	strcpy_s(m_szMapAddress,"DM70");
}

void R_toPA_Position::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x46;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,Z_ToPA_Positon,std::string,"Z_ToPA_Positon")
Z_ToPA_Positon::Z_ToPA_Positon()
{
	strcpy_s(m_szMapAddress,"DM100");
}

void Z_ToPA_Positon::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x64;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,X_ToPA_Positon,std::string,"X_ToPA_Positon")
X_ToPA_Positon::X_ToPA_Positon()
{
	strcpy_s(m_szMapAddress,"DM105");
}

void X_ToPA_Positon::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x69;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,Z_ToLoadlock_Positon,std::string,"Z_ToLoadlock_Positon")
Z_ToLoadlock_Positon::Z_ToLoadlock_Positon()
{
	strcpy_s(m_szMapAddress,"DM115");
}

void Z_ToLoadlock_Positon::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x73;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,R_ToLoadlock_Positon,std::string,"R_ToLoadlock_Positon")
R_ToLoadlock_Positon::R_ToLoadlock_Positon()
{
	strcpy_s(m_szMapAddress,"DM118");
}

void R_ToLoadlock_Positon::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x76;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,X_ToLoadlock_Positon,std::string,"X_ToLoadlock_Positon")
X_ToLoadlock_Positon::X_ToLoadlock_Positon()
{
	strcpy_s(m_szMapAddress,"DM1120");
}

void X_ToLoadlock_Positon::_BuildAddress2Send()
{
	m_pCommand[13] = 0x00;
	m_pCommand[14] = 0x78;
	m_pCommand[15] = 0x00;
}