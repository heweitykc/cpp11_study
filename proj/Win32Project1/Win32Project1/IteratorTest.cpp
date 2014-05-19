#include "stdafx.h"
#include "IteratorTest.h"

#include <algorithm>
#include <vector>

using namespace std;

void IteratorTest::doit()
{
	//指针迭代器
	//容器迭代器
	vector<int> intVector(100);
	intVector[21] = 50;
	vector<int>::iterator intIter = find(intVector.begin(), intVector.end(), 50);
	//常量迭代器

	//输入迭代器
	//输出迭代器
	double darray[10] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9 };
	vector<double> vDouble;
	vector<double>::iterator outputIterator = vDouble.begin();
	copy(darray, darray+10, outputIterator);	//拷贝数据
	while (outputIterator != vDouble.end()){
		outputIterator++;
	}
	//前推迭代器
	replace(vDouble.begin(), vDouble.end(), 1.1, 3.1415926);	//将范围内1.1替换为3.1415926
	//双向迭代器
	reverse(vDouble.begin(), vDouble.end());
	//随机访问迭代器
	random_shuffle(vDouble.begin(), vDouble.end());
}
