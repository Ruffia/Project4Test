#include "stdafx.h"
#include "OperateCommandBase.h"

void COperateCommandBase::_Initialize()
{
	m_pCommand = new byte[19];
	memset(m_pCommand,19,0);

	m_pResp = new byte[16];
	memset(m_pResp,16,0);
}


bool COperateCommandBase::CheckResponse()
{
	//C0H 00H 02H 00H 0AH	00H 00H	01H	00H 00H	01H 02H	00 00H
    int nSeq = 0;
	CHECK_RESP(0xC0)
	CHECK_RESP(0x00)
	CHECK_RESP(0x02)
	CHECK_RESP(0x00)
	CHECK_RESP(0x0A)
	CHECK_RESP(0x00)
	CHECK_RESP(0x00)
	CHECK_RESP(0x01)
	CHECK_RESP(0x00)
	CHECK_RESP(0x00)
	CHECK_RESP(0x01)
	CHECK_RESP(0x02)
	CHECK_RESP(0x00)
	CHECK_RESP(0x00)
	return true;
}


void COperateCommandBase::_BuildOperateData()
{
	m_pCommand[10] = 0x01;
	m_pCommand[11] = 0x02;
}


void COperateCommandBase::_BuildStorageCode()
{
	m_pCommand[12] = 0x30;
}


void COperateCommandBase::_BuildLength()
{
	m_pCommand[16] = 0x00;
	m_pCommand[17] = 0x01;
}


void COperateCommandBase::_BuildData()
{
	m_pCommand[18] = 0x01;
}