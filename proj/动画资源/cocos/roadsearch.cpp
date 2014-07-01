#include "roadserach.h"

void RoadSearch::init()
{
	for(int i=0; i<WIDTH; i++)
		for(int j=0; j<HEIGHT; j++)
		{
			_roads[i][j] = 0;
		}
}

void RoadSearch::update(int x, int y, int pid)
{
	_roads[i][j] = pid;
}

bool RoadSearch::findPath(int startx, int starty)
{
	_startNode = &(_roads[_startx][_starty]);
	return search();
}

bool RoadSearch::search()
{
	
}