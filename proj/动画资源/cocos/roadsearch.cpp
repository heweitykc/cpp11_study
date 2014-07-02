#include "roadsearch.h"

void RoadSearch::init()
{

}

void RoadSearch::update(int x, int y, int pid)
{
	_roads[x][y].pid = pid;
}

bool RoadSearch::findPath(int startx, int starty)
{
	_startNode = &(_roads[startx][starty]);
	_startNode->g = 0;
	_startNode->h = euclidian(_startNode);
	_startNode->f = _startNode->g + _startNode->h;

	return search();
}

bool RoadSearch::search()
{
	Node* node = _startNode;
	while (node != _endNode){
		int startX = MAX(0, node->x-1);
		int endX = MIN(Road::WIDTH-1, node->x+1);
		int startY = MAX(0, node->y-1);
		int endY = MIN(Road::HEIGHT - 1, node->y+1);
		for (int i = startX; i <= endX; i++){
			for (int j = startX; j <= endX; j++){
				Node* test = &(_roads[i][j]);
				if (test == node || test->pid > 0 || _roads[node->x][test->y].pid > 0 || _roads[test->x][node->y].pid > 0)
					continue;
				float cost = _straightCost;
				if (!(node->x == test->x) || (node->y == test->y))
					cost = _diagCost;
				float g = node->g + cost * test->costMultiplier;
				float h = euclidian(test);
				float f = g + h;
				if (isOpen(test) || isClosed(test)){
					test->f = f;
					test->g = g;
					test->h = h;
					test->parent = node;
				} else {
					test->f = f;
					test->g = g;
					test->h = h;
					test->parent = node;
					_open.push_back(test);
				}
			}
		}
		_closed.push_back(node);
		if (_open.size() == 0){
			return false;
		}
		// _open.sortOn("f", Array.NUMERIC);
		node = _open.removeLastObject()
	}

	return true;
}

float RoadSearch::euclidian(Node* node)
{
	float dx = node->x - _endNode->x;
	float dy = node->y - _endNode->y;
	return sqrt(dx * dx + dy * dy) * _straightCost;
}