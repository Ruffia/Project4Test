#include "stdafx.h"
#include "OperateCommand.h"
#include "Factory.h"
#include <string>

IMPLEMENT_FACTORY(IPLCCommand,SendWafer_Initial,std::string,"SendWafer_Initial")
SendWafer_Initial::SendWafer_Initial()
{
	strcpy_s(m_szMapAddress,"CIO5000.00");
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
}

void RemoveWafer_G2Open::_BuildAddress2Send()
{
	m_pCommand[13] = 0x13;
	m_pCommand[14] = 0x88;
	m_pCommand[15] = 0x09;
}


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
