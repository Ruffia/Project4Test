#include <iostream>
#include <stdlib.h>
using namespace std;
#include <windows.h>
#include "process.h" 

DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
static int iGolbalCount = 0;
const int iMax = 2000;
CRITICAL_SECTION cs; 


DWORD WINAPI ThreadRead(LPVOID lpParam)
{	
	char* sFlag = (char*)(lpParam);
	while (TRUE)	
	{		
		EnterCriticalSection(&cs);			
		char sz[256] = {0};
		sprintf_s(sz,256,"%s, iGolbalCount = %d\n",sFlag,iGolbalCount);
		cout<<sz<<endl;	
		if (iMax > iGolbalCount )
		{
			LeaveCriticalSection(&cs);
		}
		else
		{
			LeaveCriticalSection(&cs);
			break;
		}
		
		Sleep(10);
	}		

	return 0;
}  


DWORD WINAPI ThreadWrite(LPVOID lpParam)
{	
	char* sFlag = (char*)(lpParam);
	while (TRUE)	
	{		
		EnterCriticalSection(&cs);			
		if (iGolbalCount < iMax)		
		{	
			iGolbalCount++;
			char sz[256] = {0};
			sprintf_s(sz,256,"%s, iGolbalCount = %d\n",sFlag,iGolbalCount);
			cout<<sz<<endl;							
			LeaveCriticalSection(&cs);		
		}		
		else		
		{			
			LeaveCriticalSection(&cs);			
			break;		
		}		
		Sleep(10);	
	}	
	return 0;
}  

int main(int argc, char* argv[])
{	
	HANDLE hThread1, hThread2, hThread3; 	
	InitializeCriticalSection(&cs);

	char* sRead = "ThreadRead";
	hThread1 = CreateThread(NULL,0,ThreadRead,(LPVOID)sRead,0,NULL);

	char* sWrite = "ThreadWrite1";
	hThread2 = CreateThread(NULL,0,ThreadWrite,(LPVOID)sWrite,0,NULL);	

	char* sWrite2 = "ThreadWrite2";
	hThread3 = CreateThread(NULL,0,ThreadWrite,(LPVOID)sWrite2,0,NULL);	

	Sleep(50000); 	
	DeleteCriticalSection(&cs);	
	//删除临界区对象	
	printf("主线程结束!\n");	
	return 0;
} 

