#include <iostream>
using namespace std;

char cTrial_Array[] = "kysemdjbrc";	// "0123456789"
void Trial_Encryption(const char* cTimeSrc, char* cTimeCvt )
{
	char ch;
	// 加密
	int nLength = strlen( cTimeSrc );
	for( int i=0; i<nLength; i++ )
	{
		ch = cTimeSrc[i];
		cTimeCvt[i] = cTrial_Array[atoi(&ch)];
	}
	// swap 2,5
	ch = cTimeCvt[1];
	cTimeCvt[1] = cTimeCvt[4];
	cTimeCvt[4] = ch;
	if( nLength > 6 )
	{
		// swap 3,7
		ch = cTimeCvt[2];
		cTimeCvt[2] = cTimeCvt[6];
		cTimeCvt[6] = ch;
	}
}

bool Trial_Decryption(const char* cTimeCvt, char* cTimeSrc )
{
	char ch;
	// 解密
	int nLength = strlen( cTimeCvt );
	int nLengthA = strlen( cTrial_Array );
	for( int i=0; i<nLength; i++ )
	{
		ch = cTimeCvt[i];
		for( int j=0; j<nLengthA; j++ )
		{
			if( ch == cTrial_Array[j] )
			{
				cTimeSrc[i] = '0' +j;
				break;
			}
		}
	}
	// swap 2,5
	if( nLength > 4 )
	{
		ch = cTimeSrc[1];
		cTimeSrc[1] = cTimeSrc[4];
		cTimeSrc[4] = ch;
	}
	if( nLength > 6 )
	{
		// swap 3,7
		ch = cTimeSrc[2];
		cTimeSrc[2] = cTimeSrc[6];
		cTimeSrc[6] = ch;
	}

	bool bLegal= true;
	// 校验一下，如果有非密钥字符，则认为试用期结束
	nLength = strlen( cTimeSrc );
	for(int i=0; i<nLength; i++ )
	{
		if( cTimeSrc[i] < 0x30 || cTimeSrc[i] > 0x39 )
		{
			bLegal = false;
			break;
		}
	}
	return bLegal;
}

void EncryAndDecry(const char* s ) 
{
	cout<<s<<endl;

	char cTimeCvt[20] = {0};
	Trial_Encryption(s,cTimeCvt);
	cout<<cTimeCvt<<endl;

	char cTimeSrc[20] = {0};
	Trial_Decryption(cTimeCvt,cTimeSrc);
	cout<<cTimeSrc<<endl;
}

int Trial_CheckValid(const char* cTrialCvt, const char* cTimeCvt )
{
	int nRet = -1;	// 版本信息或时长信息的长度不符合要求
	int m_nTrialTime = 0;
	int nLengTrial = strlen( cTrialCvt );
	int nLengTime = strlen( cTimeCvt );
	if( nLengTrial == 8 && nLengTime == 8 )
	{
		char cTime[20]	= "xxxxxxxx";
		char cTrial[20]	= "xxxxxxxx";
		bool bTrial = Trial_Decryption( cTrialCvt, cTrial );
		bool bTime = Trial_Decryption( cTimeCvt, cTime );
		if( bTrial && bTime )
		{
			// 4. 有，则比较试用期是否超出
			char cVer[10] = "xxxx";
			strncpy( cVer, cTrial+4, 4 );		// 得到版本信息
			int nCmp1 = strcmp( cVer, "4137" );
			int nCmp2 = strcmp( cVer, "5268" );
			m_nTrialTime = atoi( cTime );
			cout<<"m_nTrialTime = "<<m_nTrialTime<<endl;
			cout<<"剩余天数"<<m_nTrialTime /(24*60*60)<<endl;
			if( (nCmp1 != 0) && (nCmp2 != 0) )
				nRet = -4;		// 版本信息既不是试用版也不是正式版
			else if( (nCmp1 == 0) && (m_nTrialTime > 30*24*60*60 +999) )
				nRet = -5;		// 试用版，但试用时长超出
			else if( (nCmp1 == 0) && (m_nTrialTime == 0) )
				nRet = 0;		// 有效期到期
			else if( (nCmp2 == 0) || ( (nCmp1 == 0) && (m_nTrialTime > 0) ))
			{
				if( nCmp1 == 0 )
					nRet = 1;	// 有效期内的试用版
				else
					nRet = 2;	// 正式版
			}
		}
		else
		{
			if( !bTrial )
				nRet = -2;		// 版本信息含非法字符
			else if( !bTime )
				nRet = -3;		// 时长信息含非法字符
		}
	}
	return nRet;
}


int main()
{
	{
		
		char* s = "202006304137";
		EncryAndDecry(s);
	}


	{
		char* s = "02592042";
		EncryAndDecry(s);
	}

	//strcpy( cBuf, cTrialCvt );
	//strcat( cBuf, cTimeCvt );

	char* cBuf = "skekkjskmyebksmcskds";
	cout<<cBuf<<endl;

	char cTrial[20] = {0};
	char cTrialCvt[20] = "xxxxxxxx";
	char cTime[20] = {0};
	char cTimeCvt[20] = "xxxxxxxx";

	strncpy( cTrialCvt, cBuf, 8 );
	cout<<cTrialCvt<<endl;
	strncpy( cTimeCvt, cBuf+8, 8 );
	cout<<cTimeCvt<<endl;

	int nRet = Trial_CheckValid( cTrialCvt, cTimeCvt );

	return 0;
}