// texturetool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>

using namespace std;

const int SIZE = 11;
const int ALLSIZE = SIZE * SIZE;

struct wh{
	int w;
	int h;
};

array<wh*, ALLSIZE> allSizes;	//所有可能的尺寸
vector<wh> outputlist;

void initall();
void printall();

int _tmain(int argc, _TCHAR* argv[])
{
	initall();
	printall();
	scanf_s("..%d");
	return 0;
}

void initall()
{
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			int index = i*SIZE + j;
			allSizes[index] = new wh();
			allSizes[index]->w = pow(2.0, i+1);
			allSizes[index]->h = pow(2.0, j+1);
		}
	}
}

void printall()
{
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			int index = i*SIZE + j;
			printf("w=%d,h=%d\n", allSizes[index]->w, allSizes[index]->h);
		}
	}
}