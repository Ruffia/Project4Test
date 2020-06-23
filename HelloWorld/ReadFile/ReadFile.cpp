#include <fstream> 
#include <iostream> 
using namespace std; 

int main() 
{ 
	ifstream fin("G:/Project/HelloWorld/Bin/Test.ini"); 
	char c = '\0';
	char sz[1024] = {0};
	int n = 0;
	while((c = fin.get())!=EOF) 
	{ 
		sz[n++] = c; 
	} 

	cout<<sz;
	fin.close(); 
	return 0; 
} 