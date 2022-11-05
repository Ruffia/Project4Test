#pragma once
#include "A.h"

class C
{
public:
	C();
	C(const C& obj);
	C& operator=(const C &obj);

	A& GetA()
	{
		return m_A;
	}

protected:
	A m_A;
};