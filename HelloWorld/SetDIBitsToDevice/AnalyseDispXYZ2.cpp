// MCICard.cpp : implementation file
//

#include "stdafx.h"
#include "Ddutil.h"
#include "MCICard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCICard

extern	TCHAR	g_exeFullPath[255];
extern	int		g_index;

DWORD CMCICard::ADxyz2( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if( lpBuff == NULL )
		return 0;

	LPSTR		lpDIBHdr, lpDIBBits;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	lImageLineOffset	= m_szImage.cx;
	////////////////////////////////////////////////////////////////////

	if( m_bNeedMon )
	{
		unsigned long cbRet;
		TCHAR Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format(_T("%Y%m%d-%H%M%S"));
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		_stprintf(Buf, _T("/BEGIN set z value\\\r\n"));
		WriteFile(m_hFileLog, Buf, _tcslen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}

	DWORD dwOffset = 0;
	unsigned long lSize = 0;
	unsigned long cbRet;
	char Buf[32];
	int		i, j, k, nLoop, nCounts, nIndexY1, nIndexY2;
	unsigned short* pnFrameData;

	BOOL bLastIsX, bLastIsY, bLastIsZa, bIsX, bIsY, bIsZa, bIsZb;
	unsigned short dwData	= 0;
	CSize sz = m_szImage;
	DWORD dwMaskX	= 0x8000;	// X ������
	DWORD dwMaskY	= 0x4000;	// Y ������
	DWORD dwMaskZ	= 0x0;		// Z ������
	DWORD dwMaskBOL	= 0x1000;	// BOL ������
	DWORD dwMaskBOF	= 0x3000;	// BOF ������
	DWORD dwBitsOn;
	int nValidX		= sz.cx /2;
	int nValidY		= sz.cy;
	DWORD dwDestWidthAbs	= m_rcDestFrame.Width();
	DWORD dwDestHeightAbs	= m_rcDestFrame.Height();
	DWORD dwDestWidthRel	= m_rcDestFrame.left + m_rcDestFrame.Width();
	DWORD dwDestHeightRel	= m_rcDestFrame.top + m_rcDestFrame.Height();
	bLastIsZa	= (m_dwZa != 0xFFFF);
	if( bLastIsZa )
	{
		bLastIsX = FALSE;
		bLastIsY = FALSE;
	}
	else	//if( bLastIsZa )
	{
		bLastIsY = (m_dwY != 0xFFFF);
		if( bLastIsY )
			bLastIsX = FALSE;
		else
			bLastIsX = (m_dwX != 0xFFFF);
	}

	for( j=0; j<LOOP_COUNTS; j++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];
		if( lSize > 31000 )
		{
			// 15.10.08 ��MainLoop����ͬ�����⣿����
			// �����MainLoop��Read���ǲ�����Write���ͻ����doѭ��
			// ����ʱ�����ݴ洢��������Ч����
			//
			// Scan���趨��dwDataSize������30000
			// �ڴ˼�һ���ܸ����жϣ����Ա�����ν����
			continue;
		}

		/////////////////////////////////////////////////////////////
		// ��������
		/////////////////////////////////////////////////////////////
//		dwCounts = PixConvertXYZ( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ );
		// ��Ϊÿ�����ݵĵ�һ�������ܸ���������nLoopҪ+1����ѭ��ʱ��1��ʼ
		pnFrameData = &(((unsigned short*)lpBuff)[dwOffset]);
		nLoop = lSize +1;

		bIsX		= FALSE;		// ��ǰ������X
		bIsY		= FALSE;		// ��ǰ������Y
		bIsZa		= FALSE;		// ��ǰ������Za
		bIsZb		= FALSE;		// ��ǰ������Zb
		nCounts		= 0;			// ��Ч�����ݸ���

		for( k=1; k<nLoop; k++ )
		{
			dwData = pnFrameData[k];
			// �õ����������λ
			dwBitsOn = dwData & 0xF000;

			if( bLastIsX )						// ��һ��������X
			{
				bIsY = (dwBitsOn == dwMaskY);
				if( bIsY )						// ��һ��ȷ���Ƿ�ǰ������Yֵ
					m_dwY = dwData & 0x0FFF;
			}
			if( bLastIsY )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZa		= TRUE;
				}
				else if( dwBitsOn == dwMaskBOF )
				{
					m_bPeakY	= FALSE;		// 13.02.28 ����BOF�ָ���־λPeakY
					bIsZa		= TRUE;
				}
				else
				{
					bIsZa = (dwBitsOn == dwMaskZ);	// ��һ��ȷ���Ƿ�ǰ������Zֵ
				}
				if( bIsZa )
					m_dwZa = dwData & 0x0FFF;
			}
			if( bLastIsZa )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZb		= TRUE;
				}
				else if( dwBitsOn == dwMaskBOF )
				{
					m_bPeakY	= FALSE;		// 13.02.28 ����BOF�ָ���־λPeakY
					bIsZb		= TRUE;
				}
				else
					bIsZb = (dwBitsOn == dwMaskZ);
			}
			if( bLastIsZa )
			{
/*				if( !m_bUrgency && (dwData & 0x0001) == 0x0001 )
				{
					// ������ж����󣬿����Ǹ�ѹ����֮��Ľ�������
					// ��Z�����λ��ͨ��m_pMPComm����λ������������Ϣ
					if( m_pMPComm != NULL )
					{
						// ���жϷ�����֪ͨ��λ��
						USB_SEM_ControlMessage	mciMSG;
						mciMSG.bType			= 0x0;
						mciMSG.bCtlMSGLength	= 2;
						mciMSG.bMessageID		= 0x02;	//USB_TTTT_INT;
						mciMSG.bData[1]			= 0xFF;	// ��֪���жϺţ���Ҫ��λ����ȡ�˿�B
						m_pMPComm->USB_PostMSGtoHost( mciMSG );
						m_bUrgency = TRUE;
					}
				}
*/
				// Ӳ�������Ǵ�1��ʼ�����Ҫ��0��ʼ��������Ҫ����
				if( m_dwX > m_nXOffset && m_dwY > m_nYOffset )
				{
					// �������
					if( (m_dwX <= dwDestWidthAbs +m_nXOffset) && (m_dwY <= dwDestHeightAbs +m_nYOffset) )	// 13.02.22
					{
						if( !m_bPeakX && !m_bPeakY )
						{
							// X,Y,Za���ҵ��ˣ��������
							// ������Za
							m_pPixX[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left;
							m_pPixY[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//							pPixZ[nCounts] = m_dwZa /16;	// 12λ��Zȡ��8λ(����4λ)
							if( m_bDebugZ )
								m_dwZa = m_dwZa & 0x0FFF;
							else
							{
//								if( (m_dwZa & 0x0FFF) > 0x7FF )
//									m_dwZa = 0x7FF;
//								m_dwZa = (m_dwZa & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
								if( m_dwZa > 2559)
									m_dwZa = 2559;
//								if( m_dwZa < 0x600 )
//									m_dwZa = 0x600;
								m_dwZa = (m_dwZa/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
							}
							m_pPixZ[nCounts] = m_dwZa;
//							nCounts++;
							// ���ZbҲ�ҵ���
							if( bIsZb )
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//								pPixZ[nCounts] = (dwData & 0x0FFF) /16;	// 12λ��Zȡ��8λ(����4λ)
								if( m_bDebugZ )
									dwData = dwData & 0x0FFF;
								else
								{
//									if( (dwData & 0x0FFF) > 0x7FF )
//										dwData = 0x7FF;
//									dwData = (dwData & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
									if( dwData > 2559)
										dwData = 2559;
//									if( dwData < 0x600 )
//										dwData = 0x600;
									dwData = (dwData/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
								}
								m_pPixZ2[nCounts] = dwData;
//								nCounts++;
							}
							else
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
								m_pPixZ2[nCounts] = 0x0;
							}
							nCounts++;

							if( (m_dwX == dwDestWidthAbs +m_nXOffset) && (m_dwY < dwDestHeightAbs +m_nYOffset) )	// 13.02.22
								m_bPeakX = TRUE;
							else if( (m_dwX == dwDestWidthAbs +m_nXOffset) && (m_dwY == dwDestHeightAbs +m_nYOffset) )
								m_bPeakY = TRUE;

							m_dwX = 0xFFFF;
							m_dwY = 0xFFFF;
							m_dwZa	= 0xFFFF;
						}
						else
						{
							m_dwX	= 0xFFFF;
							m_dwY	= 0xFFFF;
							m_dwZa	= 0xFFFF;
							bIsZa	= FALSE;
						}
					}
				}
				else
				{
					// ����X/Y�ķ���Ч���ݶ�(valley)��Ҫ���¸�ֵ
					m_dwX	= 0xFFFF;
					m_dwY	= 0xFFFF;
					m_dwZa	= 0xFFFF;
					bIsZa	= FALSE;
				}
			}

			bIsX = (dwBitsOn == dwMaskX);		//(dwBitsOn == dwMaskX) ? TRUE : FALSE;
			if( bIsX )							// ��һ��ȷ���Ƿ�ǰ������Xֵ
				m_dwX = dwData & 0x0FFF;

			// ˢ�±�־λ
			bLastIsX	= bIsX;
			bLastIsY	= bIsY;
			bLastIsZa	= bIsZa;
			bIsX		= FALSE;
			bIsY		= FALSE;
			bIsZa		= FALSE;
			bIsZb		= FALSE;
		}
		///////////////////////////////////////////////////////////////////////////

		if( m_bStopScan )
			break;

		if( nCounts > 0 )
		{
			/////////////////////////////////////////////////////////////
			// ����ʾ����
			/////////////////////////////////////////////////////////////
//			UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ, -1, 0, m_szOscill.cx );
//			UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ2, -1, 0, m_szOscill.cx );
			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ˢ��ͼ������
			/////////////////////////////////////////////////////////////
			if( m_bDebugZ )
			{
				for( i=0; i<nCounts; i++ )
				{
					// set z value to point(x,y)
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)(m_pPixZ[i]/16);
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)(m_pPixZ2[i]/16);
				}
			}
			else
			{
				// ����Zmix
				for( i=0; i<nCounts; i++ )
				{
					m_pPixZmix[i] = (BYTE)((m_pPixZ[i] + m_pPixZ2[i])/2);
				}
				if( m_nChnIndex[0] == 0 )
				{
					// �����ʾZa
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[0] == 1 )
				{
					// �����ʾZb
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ2[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ2, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[0] == 2 )
				{
					// �����ʾ��ͨ��ƽ��ֵ
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZmix[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZmix, -1, 0, m_szOscill.cx );
				}
				if( m_nChnIndex[1] == 0 )
				{
					// �Ҳ���ʾZa
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZ[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[1] == 1 )
				{
					// �Ҳ���ʾZb
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZ2[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ2, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[1] == 2 )
				{
					// �Ҳ���ʾ��ͨ��ƽ��ֵ
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZmix[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZmix, -1, 0, m_szOscill.cx );
				}
			}
			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ��¼����
			/////////////////////////////////////////////////////////////
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				for( i=0; i<nCounts; i++ )
				{
					sprintf(Buf, "%04X\t%04X\t%04X\t%04X\t%04X\t%d\t%d\t%d\t%d\t%d\r\n", m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i], m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
		}
		/////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// ˢ��ͼ������
		/////////////////////////////////////////////////////////////
		if( nCounts > 0 )
		{
			nIndexY1 = m_pPixY[0];
			nIndexY2 = m_pPixY[nCounts -1];
		}
		if( m_szImage.cy > 512 )
		{
			if( nIndexY1 < nIndexY2 )
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, nIndexY2+1) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, nIndexY1, m_rcDestFrame.right +nValidX, nIndexY2+1) );
			}
			else
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_rcDestFrame.top, m_szImage.cx, nIndexY2+1) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, nIndexY1, m_rcDestFrame.right +nValidX, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, m_rcDestFrame.top, m_szImage.cx +nValidX, nIndexY2+1) );
			}
//			m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_dwMinY, m_rcDestFrame.right, m_dwMaxY) );
		}
		else
			m_UpdateRectsImage.Add( rcFrame );

		/////////////////////////////////////////////////////////////
		// ��������
		dwOffset = (j+1) *(m_dwExpectantDMABlockSize +512);
		/////////////////////////////////////////////////////////////
	}
	/////////////////////////////////////////////////////////////
	g_index++;
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}

DWORD CMCICard::ADxyzLine2( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if( lpBuff == NULL )
		return 0;

	LPSTR		lpDIBHdr, lpDIBBits;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	lImageLineOffset	= m_szImage.cx;
	////////////////////////////////////////////////////////////////////

	if( m_bNeedMon )
	{
		unsigned long cbRet;
		TCHAR Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format(_T("%Y%m%d-%H%M%S"));
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		_stprintf(Buf, _T("/BEGIN set z value\\\r\n"));
		WriteFile(m_hFileLog, Buf, _tcslen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}

	DWORD dwOffset = 0;
	unsigned long lSize = 0;
	unsigned long cbRet;
	char Buf[32];
	int		i, j, k, nLoop, nCounts;
	unsigned short* pnFrameData;

	BOOL bLastIsX, bLastIsY, bLastIsZa, bIsX, bIsY, bIsZa, bIsZb;
	unsigned short dwData	= 0;
	CSize sz = m_szImage;
	DWORD dwMaskX	= 0x8000;	// X ������
	DWORD dwMaskY	= 0x4000;	// Y ������
	DWORD dwMaskZ	= 0x0;		// Z ������
	DWORD dwMaskBOL	= 0x1000;	// BOL ������
	DWORD dwMaskBOF	= 0x3000;	// BOF ������
	DWORD dwBitsOn;
	int nValidX		= sz.cx /2;
	int nValidY		= sz.cy;
	DWORD dwDestWidthAbs	= m_rcDestFrame.Width();
	DWORD dwDestHeightAbs	= m_rcDestFrame.top;	// m_rcDestFrame.Height();
	bLastIsZa	= (m_dwZa != 0xFFFF);
	if( bLastIsZa )
	{
		bLastIsX = FALSE;
		bLastIsY = FALSE;
	}
	else	//if( bLastIsZa )
	{
		bLastIsY = (m_dwY != 0xFFFF);
		if( bLastIsY )
			bLastIsX = FALSE;
		else
			bLastIsX = (m_dwX != 0xFFFF);
	}

	for( j=0; j<LOOP_COUNTS; j++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];
		if( lSize > 31000 )
		{
			// 15.10.08 ��MainLoop����ͬ�����⣿����
			// �����MainLoop��Read���ǲ�����Write���ͻ����doѭ��
			// ����ʱ�����ݴ洢��������Ч����
			//
			// Scan���趨��dwDataSize������30000
			// �ڴ˼�һ���ܸ����жϣ����Ա�����ν����
			continue;
		}

		/////////////////////////////////////////////////////////////
		// ��������
		/////////////////////////////////////////////////////////////
//		dwCounts = PixConvertXYZ( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ );
		// ��Ϊÿ�����ݵĵ�һ�������ܸ���������nLoopҪ+1����ѭ��ʱ��1��ʼ
		pnFrameData = &(((unsigned short*)lpBuff)[dwOffset]);
		nLoop = lSize +1;

		bIsX		= FALSE;		// ��ǰ������X
		bIsY		= FALSE;		// ��ǰ������Y
		bIsZa		= FALSE;		// ��ǰ������Za
		bIsZb		= FALSE;		// ��ǰ������Zb
		nCounts		= 0;			// ��Ч�����ݸ���

		for( k=1; k<nLoop; k++ )
		{
			dwData = pnFrameData[k];
			// �õ����������λ
			dwBitsOn = dwData & 0xF000;

			if( bLastIsX )						// ��һ��������X
			{
				bIsY = (dwBitsOn == dwMaskY);
				if( bIsY )						// ��һ��ȷ���Ƿ�ǰ������Yֵ
					m_dwY = dwData & 0x0FFF;
			}
			if( bLastIsY )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZa		= TRUE;
				}
				else
				{
					bIsZa = (dwBitsOn == dwMaskZ);	// ��һ��ȷ���Ƿ�ǰ������Zֵ
				}
				if( bIsZa )
					m_dwZa = dwData & 0x0FFF;
			}
			if( bLastIsZa )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZb		= TRUE;
				}
				else
					bIsZb = (dwBitsOn == dwMaskZ);
			}
			if( bLastIsZa )
			{
/*				if( !m_bUrgency && (dwData & 0x0001) == 0x0001 )
				{
					// ������ж����󣬿����Ǹ�ѹ����֮��Ľ�������
					// ��Z�����λ��ͨ��m_pMPComm����λ������������Ϣ
					if( m_pMPComm != NULL )
					{
						// ���жϷ�����֪ͨ��λ��
						USB_SEM_ControlMessage	mciMSG;
						mciMSG.bType			= 0x0;
						mciMSG.bCtlMSGLength	= 2;
						mciMSG.bMessageID		= 0x02;	//USB_TTTT_INT;
						mciMSG.bData[1]			= 0xFF;	// ��֪���жϺţ���Ҫ��λ����ȡ�˿�B
						m_pMPComm->USB_PostMSGtoHost( mciMSG );
						m_bUrgency = TRUE;
					}
				}
*/
				// Ӳ�������Ǵ�1��ʼ�����Ҫ��0��ʼ��������Ҫ����
				if( m_dwX > m_nXOffset && m_dwY > m_nYOffset )
				{
					// �������
					if( (m_dwX <= dwDestWidthAbs +m_nXOffset) && (m_dwY <= dwDestHeightAbs +m_nYOffset) )	// 13.02.22
					{
						if( !m_bPeakX && !m_bPeakY )
						{
							// X,Y,Za���ҵ��ˣ��������
							// ������Za
							m_pPixX[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left;
							m_pPixY[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//							pPixZ[nCounts] = m_dwZa /16;	// 12λ��Zȡ��8λ(����4λ)
							if( m_bDebugZ )
								m_dwZa = m_dwZa & 0x0FFF;
							else
							{
//								if( (m_dwZa & 0x0FFF) > 0x7FF )
//									m_dwZa = 0x7FF;
//								m_dwZa = (m_dwZa & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
								if( m_dwZa > 2559)
									m_dwZa = 2559;
//								if( m_dwZa < 0x600 )
//									m_dwZa = 0x600;
								m_dwZa = (m_dwZa/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
							}
							m_pPixZ[nCounts] = m_dwZa;
//							nCounts++;
							// ���ZbҲ�ҵ���
							if( bIsZb )
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//								pPixZ[nCounts] = (dwData & 0x0FFF) /16;	// 12λ��Zȡ��8λ(����4λ)
								if( m_bDebugZ )
									dwData = dwData & 0x0FFF;
								else
								{
//									if( (dwData & 0x0FFF) > 0x7FF )
//										dwData = 0x7FF;
//									dwData = (dwData & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
									if( dwData > 2559)
										dwData = 2559;
//									if( dwData < 0x600 )
//										dwData = 0x600;
									dwData = (dwData/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
								}
								m_pPixZ2[nCounts] = dwData;
//								nCounts++;
							}
							else
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
								m_pPixZ2[nCounts] = 0x0;
							}
							nCounts++;

							if( (m_dwX == dwDestWidthAbs +m_nXOffset) && (m_dwY < dwDestHeightAbs +m_nYOffset) )	// 13.02.22
								m_bPeakX = TRUE;

							m_dwX = 0xFFFF;
							m_dwY = 0xFFFF;
							m_dwZa	= 0xFFFF;
						}
						else
						{
							m_dwX	= 0xFFFF;
							m_dwY	= 0xFFFF;
							m_dwZa	= 0xFFFF;
							bIsZa	= FALSE;
						}
					}
				}
				else
				{
					// ����X/Y�ķ���Ч���ݶ�(valley)��Ҫ���¸�ֵ
					m_dwX	= 0xFFFF;
					m_dwY	= 0xFFFF;
					m_dwZa	= 0xFFFF;
					bIsZa	= FALSE;
				}
			}

			bIsX = (dwBitsOn == dwMaskX);		//(dwBitsOn == dwMaskX) ? TRUE : FALSE;
			if( bIsX )							// ��һ��ȷ���Ƿ�ǰ������Xֵ
				m_dwX = dwData & 0x0FFF;

			// ˢ�±�־λ
			bLastIsX	= bIsX;
			bLastIsY	= bIsY;
			bLastIsZa	= bIsZa;
			bIsX		= FALSE;
			bIsY		= FALSE;
			bIsZa		= FALSE;
			bIsZb		= FALSE;
		}
		///////////////////////////////////////////////////////////////////////////

		if( m_bStopScan )
			break;

		if( nCounts > 0 )
		{
			// ����Zmix
			for( i=0; i<nCounts; i++ )
			{
				m_pPixZmix[i] = (BYTE)((m_pPixZ[i] + m_pPixZ2[i])/2);
			}
			/////////////////////////////////////////////////////////////
			// ����ʾ����
			/////////////////////////////////////////////////////////////
			if( m_nChnIndex[0] == 0 )
				UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ, -1, 0, m_szOscill.cx );
			else if( m_nChnIndex[0] == 1 )
				UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ2, -1, 0, m_szOscill.cx );
			else if( m_nChnIndex[0] == 2 )
				UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZmix, -1, 0, m_szOscill.cx );
			if( m_nChnIndex[1] == 0 )
				UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ, -1, 0, m_szOscill.cx );
			else if( m_nChnIndex[1] == 1 )
				UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ2, -1, 0, m_szOscill.cx );
			else if( m_nChnIndex[1] == 2 )
				UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZmix, -1, 0, m_szOscill.cx );
			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ˢ��ͼ�����ݣ����Σ���ɨ������ˢ��ͼ�����ݣ�
			/////////////////////////////////////////////////////////////
/*			if( m_bDebugZ )
			{
				for( i=0; i<nCounts; i++ )
				{
					// set z value to point(x,y)
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)(m_pPixZ[i]/16);
				}
			}
			else
			{
				for( i=0; i<nCounts; i++ )
				{
					// set z value to point(x,y)
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
				}
			}
*/			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ��¼����
			/////////////////////////////////////////////////////////////
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				for( i=0; i<nCounts; i++ )
				{
					sprintf(Buf, "%04X\t%04X\t%04X\t%04X\t%04X\t%d\t%d\t%d\t%d\t%d\r\n", m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i], m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
		}
		/////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// ��������
		dwOffset = (j+1) *(m_dwExpectantDMABlockSize +512);
		/////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// ˢ��ͼ���������Σ���ɨ������ˢ��ͼ�����ݣ�
		/////////////////////////////////////////////////////////////
/*		if( nCounts > 0 )
		{
			nIndexY1 = m_pPixY[0];
			nIndexY2 = m_pPixY[nCounts -1];
		}
		if( m_szImage.cy > 512 )
		{
			if( nIndexY1 < nIndexY2 )
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, nIndexY2+1) );
			}
			else
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_rcDestFrame.top, m_szImage.cx, nIndexY2+1) );
			}
//			m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_dwMinY, m_rcDestFrame.right, m_dwMaxY) );
		}
		else
			m_UpdateRectsImage.Add( rcFrame );
*/	}
	/////////////////////////////////////////////////////////////
	g_index++;
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}

DWORD CMCICard::ADxyzSync2( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if( m_bSyncFinished )	// ���һ֡�Ѿ���ɣ��Ͳ�������
		return 0;

	if( lpBuff == NULL )
		return 0;

	LPSTR		lpDIBHdr, lpDIBBits;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	lImageLineOffset	= m_szImage.cx;
	////////////////////////////////////////////////////////////////////

	if( m_bNeedMon )
	{
		unsigned long cbRet;
		TCHAR Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format(_T("%Y%m%d-%H%M%S"));
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		_stprintf(Buf, _T("/BEGIN set z value\\\r\n"));
		WriteFile(m_hFileLog, Buf, _tcslen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}

	DWORD dwOffset = 0;
	unsigned long lSize = 0;
	unsigned long cbRet;
	char Buf[32];
	int		i, j, k, nLoop, nCounts, nIndexY1, nIndexY2;
	unsigned short* pnFrameData;

	BOOL bLastIsX, bLastIsY, bLastIsZa, bIsX, bIsY, bIsZa, bIsZb;
	unsigned short dwData	= 0;
	CSize sz = m_szImage;
	DWORD dwMaskX	= 0x8000;	// X ������
	DWORD dwMaskY	= 0x4000;	// Y ������
	DWORD dwMaskZ	= 0x0;		// Z ������
	DWORD dwMaskBOL	= 0x1000;	// BOL ������
	DWORD dwMaskBOF	= 0x3000;	// BOF ������
	DWORD dwBitsOn;
	int nValidX		= sz.cx /2;
	int nValidY		= sz.cy;
	DWORD dwDestWidthAbs	= m_rcDestFrame.Width();
	DWORD dwDestHeightAbs	= m_rcDestFrame.Height();
	DWORD dwDestWidthRel	= m_rcDestFrame.left + m_rcDestFrame.Width();
	DWORD dwDestHeightRel	= m_rcDestFrame.top + m_rcDestFrame.Height();
	bLastIsZa	= (m_dwZa != 0xFFFF);
	if( bLastIsZa )
	{
		bLastIsX = FALSE;
		bLastIsY = FALSE;
	}
	else	//if( bLastIsZa )
	{
		bLastIsY = (m_dwY != 0xFFFF);
		if( bLastIsY )
			bLastIsX = FALSE;
		else
			bLastIsX = (m_dwX != 0xFFFF);
	}

	for( j=0; j<LOOP_COUNTS; j++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];
		if( lSize > 31000 )
		{
			// 15.10.08 ��MainLoop����ͬ�����⣿����
			// �����MainLoop��Read���ǲ�����Write���ͻ����doѭ��
			// ����ʱ�����ݴ洢��������Ч����
			//
			// Scan���趨��dwDataSize������30000
			// �ڴ˼�һ���ܸ����жϣ����Ա�����ν����
			continue;
		}

		/////////////////////////////////////////////////////////////
		// ��������
		/////////////////////////////////////////////////////////////
//		dwCounts = PixConvertXYZ( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ );
		// ��Ϊÿ�����ݵĵ�һ�������ܸ���������nLoopҪ+1����ѭ��ʱ��1��ʼ
		pnFrameData = &(((unsigned short*)lpBuff)[dwOffset]);
		nLoop = lSize +1;

		bIsX		= FALSE;		// ��ǰ������X
		bIsY		= FALSE;		// ��ǰ������Y
		bIsZa		= FALSE;		// ��ǰ������Za
		bIsZb		= FALSE;		// ��ǰ������Zb
		nCounts		= 0;			// ��Ч�����ݸ���

		for( k=1; k<nLoop; k++ )
		{
			dwData = pnFrameData[k];
			// �õ����������λ
			dwBitsOn = dwData & 0xF000;

			if( bLastIsX )						// ��һ��������X
			{
				bIsY = (dwBitsOn == dwMaskY);
				if( bIsY )						// ��һ��ȷ���Ƿ�ǰ������Yֵ
					m_dwY = dwData & 0x0FFF;
			}
			if( bLastIsY )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZa		= TRUE;
				}
				else if( dwBitsOn == dwMaskBOF )
				{
					m_bPeakY	= FALSE;		// 13.02.28 ����BOF�ָ���־λPeakY
					bIsZa		= TRUE;
				}
				else
				{
					bIsZa = (dwBitsOn == dwMaskZ);	// ��һ��ȷ���Ƿ�ǰ������Zֵ
				}
				if( bIsZa )
					m_dwZa = dwData & 0x0FFF;
			}
			if( bLastIsZa )
			{
				if( dwBitsOn == dwMaskBOL )
				{
					m_bPeakX	= FALSE;		// 13.02.28 ����BOL�ָ���־λPeakX
					bIsZb		= TRUE;
				}
				else if( dwBitsOn == dwMaskBOF )
				{
					m_bPeakY	= FALSE;		// 13.02.28 ����BOF�ָ���־λPeakY
					bIsZb		= TRUE;
				}
				else
					bIsZb = (dwBitsOn == dwMaskZ);
			}
			if( bLastIsZa )
			{
/*				if( !m_bUrgency && (dwData & 0x0001) == 0x0001 )
				{
					// ������ж����󣬿����Ǹ�ѹ����֮��Ľ�������
					// ��Z�����λ��ͨ��m_pMPComm����λ������������Ϣ
					if( m_pMPComm != NULL )
					{
						// ���жϷ�����֪ͨ��λ��
						USB_SEM_ControlMessage	mciMSG;
						mciMSG.bType			= 0x0;
						mciMSG.bCtlMSGLength	= 2;
						mciMSG.bMessageID		= 0x02;	//USB_TTTT_INT;
						mciMSG.bData[1]			= 0xFF;	// ��֪���жϺţ���Ҫ��λ����ȡ�˿�B
						m_pMPComm->USB_PostMSGtoHost( mciMSG );
						m_bUrgency = TRUE;
					}
				}
*/
				// Ӳ�������Ǵ�1��ʼ�����Ҫ��0��ʼ��������Ҫ����
				if( m_dwX > m_nXOffset && m_dwY > m_nYOffset )
				{
					// �������
					if( (m_dwX <= dwDestWidthAbs +m_nXOffset) && (m_dwY <= dwDestHeightAbs +m_nYOffset) )	// 13.02.22
					{
						if( !m_bPeakX && !m_bPeakY )
						{
							// X,Y,Za���ҵ��ˣ��������
							// ������Za
							m_pPixX[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left;
							m_pPixY[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//							pPixZ[nCounts] = m_dwZa /16;	// 12λ��Zȡ��8λ(����4λ)
							if( m_bDebugZ )
								m_dwZa = m_dwZa & 0x0FFF;
							else
							{
//								if( (m_dwZa & 0x0FFF) > 0x7FF )
//									m_dwZa = 0x7FF;
//								m_dwZa = (m_dwZa & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
								if( m_dwZa > 2559)
									m_dwZa = 2559;
//								if( m_dwZa < 0x600 )
//									m_dwZa = 0x600;
								m_dwZa = (m_dwZa/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
							}
							m_pPixZ[nCounts] = m_dwZa;
//							nCounts++;
							// ���ZbҲ�ҵ���
							if( bIsZb )
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
//								pPixZ[nCounts] = (dwData & 0x0FFF) /16;	// 12λ��Zȡ��8λ(����4λ)
								if( m_bDebugZ )
									dwData = dwData & 0x0FFF;
								else
								{
//									if( (dwData & 0x0FFF) > 0x7FF )
//										dwData = 0x7FF;
//									dwData = (dwData & 0x0FFF) /8;	// 12λ��Zȡbit10---bit3(����3λ)
									if( dwData > 2559)
										dwData = 2559;
//									if( dwData < 0x600 )
//										dwData = 0x600;
									dwData = (dwData/* -0x600*/) /10;	// ȡֵ��Χ��Ӧ255---0�Ҷȷ�Χ��ʾ
								}
								m_pPixZ2[nCounts] = dwData;
//								nCounts++;
							}
							else
							{
								m_pPixX2[nCounts] = m_dwX -m_nXOffset -1 +m_rcDestFrame.left +nValidX;
								m_pPixY2[nCounts] = m_dwY -m_nYOffset -1 +m_rcDestFrame.top;
								m_pPixZ2[nCounts] = 0x0;
							}
							nCounts++;

							if( (m_dwX == dwDestWidthAbs +m_nXOffset) && (m_dwY < dwDestHeightAbs +m_nYOffset) )	// 13.02.22
								m_bPeakX = TRUE;
							else if( (m_dwX == dwDestWidthAbs +m_nXOffset) && (m_dwY == dwDestHeightAbs +m_nYOffset) )
							{
								m_bPeakY = TRUE;
								m_bSyncFinished = TRUE;
								break;	//return nCounts;
							}

							m_dwX = 0xFFFF;
							m_dwY = 0xFFFF;
							m_dwZa	= 0xFFFF;
						}
						else
						{
							m_dwX	= 0xFFFF;
							m_dwY	= 0xFFFF;
							m_dwZa	= 0xFFFF;
							bIsZa	= FALSE;
						}
					}
				}
				else
				{
					// ����X/Y�ķ���Ч���ݶ�(valley)��Ҫ���¸�ֵ
					m_dwX	= 0xFFFF;
					m_dwY	= 0xFFFF;
					m_dwZa	= 0xFFFF;
					bIsZa	= FALSE;
				}
			}

			bIsX = (dwBitsOn == dwMaskX);		//(dwBitsOn == dwMaskX) ? TRUE : FALSE;
			if( bIsX )							// ��һ��ȷ���Ƿ�ǰ������Xֵ
				m_dwX = dwData & 0x0FFF;

			// ˢ�±�־λ
			bLastIsX	= bIsX;
			bLastIsY	= bIsY;
			bLastIsZa	= bIsZa;
			bIsX		= FALSE;
			bIsY		= FALSE;
			bIsZa		= FALSE;
			bIsZb		= FALSE;
		}
		///////////////////////////////////////////////////////////////////////////

		if( m_bStopScan )
			break;

		if( nCounts > 0 )
		{
			/////////////////////////////////////////////////////////////
			// ����ʾ����
			/////////////////////////////////////////////////////////////
//			UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ, -1, 0, m_szOscill.cx );
//			UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ2, -1, 0, m_szOscill.cx );
			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ˢ��ͼ������
			/////////////////////////////////////////////////////////////
			if( m_bDebugZ )
			{
				for( i=0; i<nCounts; i++ )
				{
					// set z value to point(x,y)
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)(m_pPixZ[i]/16);
					((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)(m_pPixZ2[i]/16);
				}
			}
			else
			{
				// ����Zmix
				for( i=0; i<nCounts; i++ )
				{
					m_pPixZmix[i] = (BYTE)((m_pPixZ[i] + m_pPixZ2[i])/2);
				}
				if( m_nChnIndex[0] == 0 )
				{
					// �����ʾZa
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[0] == 1 )
				{
					// �����ʾZb
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ2[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZ2, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[0] == 2 )
				{
					// �����ʾ��ͨ��ƽ��ֵ
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZmix[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX, m_pPixY, m_pPixZmix, -1, 0, m_szOscill.cx );
				}
				if( m_nChnIndex[1] == 0 )
				{
					// �Ҳ���ʾZa
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZ[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[1] == 1 )
				{
					// �Ҳ���ʾZb
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZ2[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZ2, -1, 0, m_szOscill.cx );
				}
				else if( m_nChnIndex[1] == 2 )
				{
					// �Ҳ���ʾ��ͨ��ƽ��ֵ
					for( i=0; i<nCounts; i++ )
					{
						// set z value to point(x,y)
						((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY2[i] - 1) * lImageLineOffset + m_pPixX2[i] ]  = (BYTE)m_pPixZmix[i];
					}
					UpdateOscillographNew( nCounts, m_pPixX2, m_pPixY2, m_pPixZmix, -1, 0, m_szOscill.cx );
				}
			}
			/////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////
			// ��¼����
			/////////////////////////////////////////////////////////////
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				for( i=0; i<nCounts; i++ )
				{
					sprintf(Buf, "%04X\t%04X\t%04X\t%04X\t%04X\t%d\t%d\t%d\t%d\t%d\r\n", m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i], m_pPixX[i], m_pPixY[i], m_pPixZ[i], m_pPixZ2[i], m_pPixZmix[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
		}
		/////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// ˢ��ͼ������
		/////////////////////////////////////////////////////////////
		if( nCounts > 0 )
		{
			nIndexY1 = m_pPixY[0];
			nIndexY2 = m_pPixY[nCounts -1];
		}
		if( m_szImage.cy > 512 )
		{
			if( nIndexY1 < nIndexY2 )
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, nIndexY2+1) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, nIndexY1, m_rcDestFrame.right +nValidX, nIndexY2+1) );
			}
			else
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, nIndexY1, m_rcDestFrame.right, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_rcDestFrame.top, m_szImage.cx, nIndexY2+1) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, nIndexY1, m_rcDestFrame.right +nValidX, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left +nValidX, m_rcDestFrame.top, m_szImage.cx +nValidX, nIndexY2+1) );
			}
//			m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_dwMinY, m_rcDestFrame.right, m_dwMaxY) );
		}
		else
			m_UpdateRectsImage.Add( rcFrame );

		CRect rcIndication = CRect(0,0,8,nIndexY2);
		PhotoIndication( rcIndication, RGB(0,0,255) );

		/////////////////////////////////////////////////////////////
		// ��������
		dwOffset = (j+1) *(m_dwExpectantDMABlockSize +512);
		/////////////////////////////////////////////////////////////
	}
	/////////////////////////////////////////////////////////////
	g_index++;
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}
