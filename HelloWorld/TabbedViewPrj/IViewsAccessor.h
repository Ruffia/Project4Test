#pragma once

class IViewsAccessor
{
public:
	IViewsAccessor(void);
public:
	~IViewsAccessor(void);
	
public:
	virtual void AccessViewsArray(CArray<CView*, CView*&>* pArrayViews)
	{
		m_pArrayViews = pArrayViews;
	}	
	
protected:
	CArray<CView*, CView*&>* m_pArrayViews;		
};
