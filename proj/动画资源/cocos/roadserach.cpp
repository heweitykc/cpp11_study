#include "roadserach.h"

void RoadSearch::init()
{
	for(int i=0; i<WIDTH; i++)
		for(int j=0; j<HEIGHT; j++)
		{
			_roads[i][j] = OPEN;
		}
}

void RoadSearch::update(int x,int y, RoadSearch::TYPE type)
{
	_roads[i][j] = type;
}