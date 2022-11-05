#include "B.h"

int B::m_nNO = 0;

B::B()
{
	m_sz = new char[64];
	memset(m_sz,0,64);
	sprintf_s(m_sz,64,"%d",m_nNO++);
	cout<<"B() "<<m_nNO <<endl;
}


B::B(const B& obj)
{
	cout<<"B() Copy" <<endl;
	m_sz = new char[64];
	memset(m_sz,0,64);
	strcpy(m_sz,obj.m_sz);
}


B& B::operator=(const B &obj)
{
	cout<<"B() =" <<endl;
	m_sz = new char[64];
	memset(m_sz,0,64);
	strcpy(m_sz,obj.m_sz);
	return *this;
}


B::~B()
{
	cout<<"~B() "<<m_nNO<<endl;
	if (m_sz)
	{
		delete m_sz;
		m_sz = NULL;
	}
}
