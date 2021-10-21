#include "stdafx.h"
#include "DebugCommandBase.h"

void CDebugCommandBase::_Initialize()
{
	m_pCommand = new byte[22];
	memset(m_pCommand,22,0);

	m_pResp = new byte[14];
	memset(m_pResp,14,0);
}


bool CDebugCommandBase::CheckResponse()
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


void CDebugCommandBase::SetParameter(byte b0,byte b1,byte b2,byte b3)
{
	m_bWrite[0] = b0;
	m_bWrite[1] = b1;
	m_bWrite[2] = b2;
	m_bWrite[3] = b3;
}


void CDebugCommandBase::_BuildOperateData()
{
	m_pCommand[10] = 0x01;
	m_pCommand[11] = 0x02;
}


void CDebugCommandBase::_BuildStorageCode()
{
	m_pCommand[12] = 0x82;
}

void CDebugCommandBase::_BuildLength()
{
	m_pCommand[16] = 0x00;
	m_pCommand[17] = 0x02;
}


void CDebugCommandBase::_BuildData()
{
	m_pCommand[18] = m_bWrite[0];
	m_pCommand[19] = m_bWrite[1];
	m_pCommand[20] = m_bWrite[2];
	m_pCommand[21] = m_bWrite[3];
}
