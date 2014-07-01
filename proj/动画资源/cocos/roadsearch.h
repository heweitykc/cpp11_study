#ifndef __ROAD_SERACH_H__
#define __ROAD_SERACH_H__

#include "cocos2d.h"

USING_NS_CC;

class RoadSearch
{
public:
	static const int WIDTH =  18;
	static const int HEIGHT = 18;
	enum TYPE {OPEN=0,CLOSE=1};
	void init();
	void update(int x,int y,int pid);

private:
	unsigned char _roads[WIDTH][HEIGHT];
	unsigned char _proads[WIDTH][HEIGHT];
};

#endif