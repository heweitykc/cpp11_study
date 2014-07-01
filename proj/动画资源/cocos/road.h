#ifndef __ROAD_H__
#define __ROAD_H__

#include "role.h"

class Road
{
public:
	static const int WIDTH =  18;
	static const int HEIGHT = 18;	

	void init();
private:
	Role role[10];	//10»ÀÕ¨∆¡	
};

#endif