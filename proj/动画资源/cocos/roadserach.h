#ifndef __ROAD_SERACH_H__
#define __ROAD_SERACH_H__

#include <string>
#include "cocos2d.h"
#include "network\WebSocket.h"
#include "pkgutil.h"

USING_NS_CC;

class RoadSearch
{
public:
	static const int WIDTH =  40;
	static const int HEIGHT = 40;
	enum TYPE {OPEN=0,CLOSE=1};
	void init();
	void update(int x,int y);
private:
	unsigned char _roads[WIDTH][HEIGHT];
};

#endif