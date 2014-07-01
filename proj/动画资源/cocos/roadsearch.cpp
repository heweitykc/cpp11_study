#include "roadserach.h"

void RoadSearch::init()
{
	for(int i=0; i<WIDTH; i++)
		for(int j=0; j<HEIGHT; j++)
		{
			_roads[i][j] = OPEN;
			_proads[i][j] = 0;
		}
}

void RoadSearch::update(int x, int y, RoadSearch::TYPE type, int pid)
{
	_roads[i][j] = type;
	_proads[i][j] = pid;
}