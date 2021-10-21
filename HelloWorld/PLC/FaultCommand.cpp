#include "stdafx.h"
#include "FaultCommand.h"
#include "Factory.h"
#include <string>

IMPLEMENT_FACTORY(IPLCCommand,DD_Motor_Overcurrent,std::string,"DD_Motor_Overcurrent")
DD_Motor_Overcurrent::DD_Motor_Overcurrent()
{
	strcpy_s(m_szMapAddress,"5020.00");
}

void DD_Motor_Overcurrent::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x9C;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,PA_Overcurrent,std::string,"PA_Overcurrent")
PA_Overcurrent::PA_Overcurrent()
{
	strcpy_s(m_szMapAddress,"5020.01");
}

void PA_Overcurrent::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x9C;
	m_pCommand[15] = 0x01;
}


IMPLEMENT_FACTORY(IPLCCommand,TA_Drive_Overcurrent,std::string,"TA_Drive_Overcurrent")
TA_Drive_Overcurrent::TA_Drive_Overcurrent()
{
	strcpy_s(m_szMapAddress,"5020.02");
}

void TA_Drive_Overcurrent::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x9C;
	m_pCommand[15] = 0x02;
}


IMPLEMENT_FACTORY(IPLCCommand,Loadlock_Drive_Overcurrent,std::string,"Loadlock_Drive_Overcurrent")
Loadlock_Drive_Overcurrent::Loadlock_Drive_Overcurrent()
{
	strcpy_s(m_szMapAddress,"5020.03");
}


void Loadlock_Drive_Overcurrent::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x9C;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(IPLCCommand,TA_VAC_Err,std::string,"TA_VAC_Err")
TA_VAC_Err::TA_VAC_Err()
{
	strcpy_s(m_szMapAddress,"5021.00");
}


void TA_VAC_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,PLC_System_Err,std::string,"PLC_System_Err")
PLC_System_Err::PLC_System_Err()
{
	strcpy_s(m_szMapAddress,"5021.03");
}

void PLC_System_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(IPLCCommand,X_Drive_Err,std::string,"X_Drive_Err")
X_Drive_Err::X_Drive_Err()
{
	strcpy_s(m_szMapAddress,"5021.04");
}

void X_Drive_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x04;
}


IMPLEMENT_FACTORY(IPLCCommand,Z_Drive_Err,std::string,"Z_Drive_Err")
Z_Drive_Err::Z_Drive_Err()
{
	strcpy_s(m_szMapAddress,"5021.05");
}

void Z_Drive_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x05;
}


IMPLEMENT_FACTORY(IPLCCommand,R_Drive_Err,std::string,"R_Drive_Err")
R_Drive_Err::R_Drive_Err()
{
	strcpy_s(m_szMapAddress,"5021.06");
}

void R_Drive_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x06;
}


IMPLEMENT_FACTORY(IPLCCommand,CV1_Drive_Err,std::string,"CV1_Drive_Err")
CV1_Drive_Err::CV1_Drive_Err()
{
	strcpy_s(m_szMapAddress,"5021.07");
}

void CV1_Drive_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x07;
}


IMPLEMENT_FACTORY(IPLCCommand,CV2_Drive_Err,std::string,"CV2_Drive_Err")
CV2_Drive_Err::CV2_Drive_Err()
{
	strcpy_s(m_szMapAddress,"5021.08");
}


void CV2_Drive_Err::_BuildAddress2Send()
{
	m_pCommand[13] = 0x14;
	m_pCommand[14] = 0x51;
	m_pCommand[15] = 0x08;
}
