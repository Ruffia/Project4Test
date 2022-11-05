#include "A.h"

A::A(int nCount):m_nCount(nCount)
{
	cout<<"A() "<<endl;
	m_pB = new B[nCount];
}

A::A(const A& obj)
{
	cout<<"A() Copy"<<endl;
	m_pB = obj.m_pB;
	m_nCount = obj.m_nCount;
}

A& A::operator=(const A &obj)
{
	cout<<"A() ="<<endl;
	m_pB = obj.m_pB;
	m_nCount = obj.m_nCount;
	return *this;
}


A::~A()
{
	cout<<"~A() "<<endl;
	if (m_pB)
	{
		delete[] m_pB;
		m_pB = NULL;
	}
}

void A::Display()
{
	for (int i = 0; i < m_nCount;i++)
	{
		B objB = m_pB[i];
		char* sMsg = objB.GetNO();
		cout<<sMsg<<endl;
	}
}