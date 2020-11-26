#include <iostream>
using namespace std;

template<class T1, class T2>
bool Compare(T1, T2)
{
	return T1 > T2;
}


#define GET_NAME(x) #x
template<typename T1, typename T2>
void TestTempFunc()
{
	cout<<"T1"<<" "<<"T2"<<endl;
}

int main()
{
	typedef void (*fp)();
	fp funcTest = TestTempFunc<int,int>;
	std::string sName = GET_NAME(funcTest);

	//typedef int (*Func)(int,int);
	//Func fTest = Compare<int,int>(int, int);
	return 0;
}
