#pragma once

#include "math.h"

class HsAlgorithm
{
public:
	HsAlgorithm();
public:
	virtual ~HsAlgorithm();		
};

class HsAreaAlgorithm : public HsAlgorithm
{
public:
	// section_info contains num of cuts or divisions across a section;
	bool DivideRectangularArea(unsigned int num_rects, /*OUT*/int& num_sections, /*OUT*/int*& section_infos);
	void ReleaseSectionInfo(int* section_infos);

}; 

