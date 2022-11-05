#pragma once
#include "B.h"

class A
{
public:
	A(int nCount = 3);

	A(const A& obj);

	A& operator=(const A &obj);

	~A();

	void Display();

public:
	B* m_pB;
	int m_nCount;
};