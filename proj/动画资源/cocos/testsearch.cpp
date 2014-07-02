#include "roadsearch.h"

int main()
{
	RoadSearch searcher;
	searcher.init();
	searcher.update(1,1, 1);
	searcher.update(2,2, 1);
	searcher.update(5,5, 1);
	searcher.findPath(0,0,5,6);
	return 0;
}