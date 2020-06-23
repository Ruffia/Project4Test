#include <stdlib.h>
#include <iostream>
using namespace std;
#include <windef.h>

////http://lostphp.com/hexconvert/

char* Float2HexString(const float f) 
{
	unsigned char *hex = (unsigned char *)&f;
	char* sHex = new char[9];
	memset(sHex,0,9);
	sprintf(sHex,"%02X%02X%02X%02X",hex[0],hex[1],hex[2],hex[3]);
	return sHex;
}

DWORD Float2DWORD(const float f) 
{
	unsigned char *hex = (unsigned char *)&f;
	char* sHex = new char[9];
	memset(sHex,0,9);
	sprintf(sHex,"%02X%02X%02X%02X",hex[0],hex[1],hex[2],hex[3]);
	DWORD dValue = (DWORD)strtoul(sHex, NULL, 16);
	delete sHex;
	sHex = NULL;
	return dValue;
}


int main()
{
	{
		float f = 1.0625f;
		unsigned char *hex = (unsigned char *)&f;
		printf("0x "); 
		for(int i = 0; i < 4; i++) 
			printf("%02X ", hex[i]); 
		printf("\n");
	}

	{
		float f = 1.0625f;
		char* sHex = Float2Hex(f);
		printf(sHex);
		printf("\n");
	}


	{
		unsigned char hex[] = { 0x00, 0x00, 0x88,0x3F };
		float f = *(float *)hex;
		printf("%g\n", f); 
	}


	return 0;
}