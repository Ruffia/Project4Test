#include "StdAfx.h"
#include "HsAlgorithm.h"

HsAlgorithm::HsAlgorithm(void)
{
}

HsAlgorithm::~HsAlgorithm(void)
{
}


bool HsAreaAlgorithm::DivideRectangularArea(unsigned int num_rects, /*OUT*/int& num_sections, /*OUT*/int*& section_infos)
{
	if(num_rects == 0)
		return false;

	
	if(num_rects < 4)
	{
		int sections = 1;
		section_infos = new int[sections];
		for(int i = 0; i < sections; i++)
		{
			section_infos[i] = num_rects;
		}
		num_sections = sections;		
	}
	else
	{
		double root = num_rects;
		double sqr_root = sqrt(root);
		int rounded_root = (int) sqr_root;
		
		int sections = rounded_root;
		int section_info = rounded_root;

		section_infos = new int[sections];
		
		int leftover = ((int) num_rects) - sections * section_info;			   	 
		
		int distrib = leftover / sections;
		section_info += distrib;
		int left = num_rects - (sections * section_info);	

		int start_adding_index = sections - left;
		
		for(int i = 0; i < sections; i++)
		{
			if(i == start_adding_index)
			{
				section_info++;
				start_adding_index = -1;				
			}
			section_infos[i] = section_info;
		}
		num_sections = sections;
	}

	return true;
}


void HsAreaAlgorithm::ReleaseSectionInfo(int* section_infos)
{
	delete[] section_infos;
}