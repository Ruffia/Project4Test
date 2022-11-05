#include "C.h"

C::C()
{
	cout<<"C()"<<endl;
}

C::C(const C& obj)
{
	cout<<"C() Copy"<<endl;
}

C& C::operator=(const C &obj)
{
	cout<<"C() ="<<endl;
	m_A = obj.m_A;
	return *this;
}