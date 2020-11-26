#include <iostream>
using namespace std;

#define GetName(MARCO) #MARCO
#define MACRO1 123
#define M2     444

template<typename T1, typename T2>
void TestTempFunc()
{
	cout<<"T1"<<" "<<"T2"<<endl;
}

void ASSD()
{
	cout<<"T1"<<" "<<"T2"<<endl;
}

int main()
{
	char* s = NULL;
	s = GetName(MACRO1);
	cout<<s<<endl;

	s = GetName(M2);
	cout<<s<<endl;

	s = GetName(TestTempFunc_int_float);
	cout<<s<<endl;

	return 0;
}