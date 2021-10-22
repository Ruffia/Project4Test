#include "stdafx.h"
#include "FunctionKeyCommand.h"
#include "Factory.h"
#include <string>


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_1,std::string,"TakingWafer_1")
TakingWafer_1::TakingWafer_1()
{
	strcpy_s(m_szMapAddress,"CIO5008.00");
}


void TakingWafer_1::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_2,std::string,"TakingWafer_2")
TakingWafer_2::TakingWafer_2()
{
	strcpy_s(m_szMapAddress,"CIO5008.01");
}


void TakingWafer_2::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x01;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_3,std::string,"TakingWafer_3")
TakingWafer_3::TakingWafer_3()
{
	strcpy_s(m_szMapAddress,"CIO5008.02");
}


void TakingWafer_3::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x02;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_4,std::string,"TakingWafer_4")
TakingWafer_4::TakingWafer_4()
{
	strcpy_s(m_szMapAddress,"CIO5008.03");
}


void TakingWafer_4::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_5,std::string,"TakingWafer_5")
TakingWafer_5::TakingWafer_5()
{
	strcpy_s(m_szMapAddress,"CIO5008.04");
}


void TakingWafer_5::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x04;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_6,std::string,"TakingWafer_6")
TakingWafer_6::TakingWafer_6()
{
	strcpy_s(m_szMapAddress,"CIO5008.05");
}


void TakingWafer_6::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x05;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_7,std::string,"TakingWafer_7")
TakingWafer_7::TakingWafer_7()
{
	strcpy_s(m_szMapAddress,"CIO5008.06");
}


void TakingWafer_7::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x06;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_8,std::string,"TakingWafer_8")
TakingWafer_8::TakingWafer_8()
{
	strcpy_s(m_szMapAddress,"CIO5008.07");
}

void TakingWafer_8::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x07;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_9,std::string,"TakingWafer_9")
TakingWafer_9::TakingWafer_9()
{
	strcpy_s(m_szMapAddress,"CIO5008.08");
}


void TakingWafer_9::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x08;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_10,std::string,"TakingWafer_10")
TakingWafer_10::TakingWafer_10()
{
	strcpy_s(m_szMapAddress,"CIO5008.09");
}


void TakingWafer_10::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x09;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_11,std::string,"TakingWafer_11")
TakingWafer_11::TakingWafer_11()
{
	strcpy_s(m_szMapAddress,"CIO5008.10");
}


void TakingWafer_11::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x0A;
}


IMPLEMENT_FACTORY(IPLCCommand,TakingWafer_12,std::string,"TakingWafer_12")
TakingWafer_12::TakingWafer_12()
{
	strcpy_s(m_szMapAddress,"CIO5008.11");
}


void TakingWafer_12::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x90;
	m_pCommand[15] = 0x0B;
}


IMPLEMENT_FACTORY(IPLCCommand,Motor_Power_On,std::string,"Motor_Power_On")
Motor_Power_On::Motor_Power_On()
{
	strcpy_s(m_szMapAddress,"CIO5009.00");
}

void Motor_Power_On::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x91;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,Motor_Power_Off,std::string,"Motor_Power_Off")
Motor_Power_Off::Motor_Power_Off()
{
	strcpy_s(m_szMapAddress,"CIO5009.01");
}


void Motor_Power_Off::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x91;
	m_pCommand[15] = 0x01;
}


IMPLEMENT_FACTORY(IPLCCommand,Motor_Enable,std::string,"Motor_Enable")
Motor_Enable::Motor_Enable()
{
	strcpy_s(m_szMapAddress,"CIO5009.04");
}

void Motor_Enable::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x91;
	m_pCommand[15] = 0x04;
}


IMPLEMENT_FACTORY(IPLCCommand,Motor_RetureZero,std::string,"Motor_RetureZero")
Motor_RetureZero::Motor_RetureZero()
{
	strcpy_s(m_szMapAddress,"CIO5001.00");
}

void Motor_RetureZero::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x89;
	m_pCommand[15] = 0x00;
}


IMPLEMENT_FACTORY(IPLCCommand,Motor_Stop,std::string,"Motor_Stop")
Motor_Stop::Motor_Stop()
{
	strcpy_s(m_szMapAddress,"CIO5001.03");
}

void Motor_Stop::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x89;
	m_pCommand[15] = 0x03;
}


IMPLEMENT_FACTORY(IPLCCommand,Position_parameter_Req,std::string,"Position_parameter_Req")
Position_parameter_Req::Position_parameter_Req()
{
	strcpy_s(m_szMapAddress,"CIO5010.00");
}

void Position_parameter_Req::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x92;
	m_pCommand[15] = 0x00;
}
