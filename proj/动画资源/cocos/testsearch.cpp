#include "roadsearch.h"
#include <time.h>
#include <iostream>
#include <windows.h>

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
	
	LARGE_INTEGER m_liPerfFreq={0};
	QueryPerformanceFrequency(&m_liPerfFreq); 
	LARGE_INTEGER m_liPerfStart={0};
	QueryPerformanceCounter(&m_liPerfStart);

	//Sleep(106);
	searcher.findPath(0,0,15,16);

	LARGE_INTEGER liPerfNow={0};
	QueryPerformanceCounter(&liPerfNow);
	int time=( ((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)/m_liPerfFreq.QuadPart);

	std::cout<<"elapse:"<<time<<endl;
	searcher.printPath();
	return 0;
}