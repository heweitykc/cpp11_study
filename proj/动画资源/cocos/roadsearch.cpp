#include "roadsearch.h"
#include <algorithm>
#include <iostream>

void RoadSearch::init()
{
	for(int i=0;i<WIDTH;i++)
		for(int j=0;j<HEIGHT;j++){
			_roads[i][j].x = i;
			_roads[i][j].y = j;
			_roads[i][j].pid = 0;
			_roads[i][j].costMultiplier = 1.0f;
		}
}

void RoadSearch::update(int x, int y, int pid)
{
	_roads[x][y].pid = pid;
}

bool RoadSearch::findPath(int startx, int starty, int endx, int endy)
{
	_startNode = &(_roads[startx][starty]);
	_startNode->g = 0;
	_startNode->h = euclidian(_startNode);
	_startNode->f = _startNode->g + _startNode->h;
	_endNode = &(_roads[endx][endy]);
	return search();
}

bool RoadSearch::search()
{
	Node* node = _startNode;

	while (node != _endNode){
		int startX = fmax(0, node->x-1);
		int endX = fmin(WIDTH-1, node->x+1);
		int startY = fmax(0, node->y-1);
		int endY = fmin(HEIGHT - 1, node->y+1);
		//cout<<startX<<" "<<startY<<" "<<endX<<" "<<endY<<endl;
		for (int i = startX; i <= endX; i++){
			for (int j = startY; j <= endY; j++){
				Node* test = &(_roads[i][j]);
				if (test == node || test->pid > 0 || _roads[node->x][test->y].pid > 0 || _roads[test->x][node->y].pid > 0)
					continue;
				float cost = _straightCost;
				if (!(node->x == test->x) || (node->y == test->y))
					cost = _diagCost;
				float g = node->g + cost * test->costMultiplier;
				float h = diagonal(test);
				float f = g + h;
				if (isOpen(test) || isClosed(test)){
					if (f<test->f){
						test->f = f;
						test->g = g;
						test->h = h;
						test->parent = node;
					}
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
		/*
		list<Node*>::iterator itr = _open.begin();
		while(itr!=_open.end()){
           cout<<(*itr)->x<<"_"<<(*itr)->y<<" ";
			itr++;
        }
		cout<<endl;*/

		if (_open.size() == 0){
			cout<<"no road"<<endl;
			return false;
		}
		_open.sort(greater_f);
		node = _open.front();
		_open.pop_front();
	}
	buildPath();
	return true;
}

float RoadSearch::euclidian(Node* node)
{
	float dx = node->x - _endNode->x;
	float dy = node->y - _endNode->y;
	return sqrt(dx * dx + dy * dy) * _straightCost;
}

float RoadSearch::diagonal(Node* node) 
 { 
 	float dx = abs(node->x - _endNode->x); 
 	float dy = abs(node->y - _endNode->y); 
 	float diag = min(dx, dy); 
 	float straight = dx + dy; 
 	return _diagCost * diag + _straightCost * (straight - 2 * diag); 
 }

void RoadSearch::buildPath()
{
	_path.clear();
	Node* node = _endNode;
	_path.push_front(node);
	//cout<<"final path:"<<endl;
	//cout<<node->x<<"_"<<node->y<<endl;
	while (node != _startNode){
		node = node->parent;
		_path.push_front(node);
		//cout<<node->x<<"_"<<node->y<<endl;
	}
}

bool RoadSearch::isOpen(Node* node)
{
	list<Node*>::iterator itr = _open.begin();
	while(itr != _open.end()){
		if((*itr) == node) return true;
		itr++;
	}
	return false;
}

bool RoadSearch::isClosed(Node* node)
{
	list<Node*>::iterator itr = _closed.begin();
	while(itr != _closed.end()){
		if((*itr) == node) return true;
		itr++;
	}
	return false;
}
