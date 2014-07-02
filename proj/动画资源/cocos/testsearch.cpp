#include "roadsearch.h"

int main()
{
	RoadSearch searcher;
	searcher.init();
	searcher.update(1,1, 1);
	searcher.update(2,2, 1);
	searcher.update(5,5, 1);
	searcher.update(5,8, 1);
	searcher.update(5,7, 1);
	searcher.update(5,4, 1);
	searcher.update(14,17, 1);
	searcher.update(14,15, 1);
	searcher.update(14,14, 1);
	searcher.update(14,13, 1);
	searcher.update(14,12, 1);
	searcher.update(14,11, 1);
	searcher.findPath(0,0,15,16);
	return 0;
}