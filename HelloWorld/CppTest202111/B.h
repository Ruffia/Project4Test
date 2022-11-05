#pragma once
#include <iostream>
using namespace std;

class B
{
public:
	B();
	B(const B& obj);
	B& operator=(const B &obj);

	~B();

	char* GetNO()
	{
		return m_sz;
	}

public:
	static int m_nNO;
	char* m_sz;
};