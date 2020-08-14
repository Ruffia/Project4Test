#include <iostream>
using namespace std;

#define GetName(MARCO) #MARCO
#define MACRO1 123
#define M2     444

int main()
{
	char* s = NULL;
	s = GetName(MACRO1);
	cout<<s<<endl;

	s = GetName(M2);
	cout<<s<<endl;

	return 0;
}