#include "stdafx.h"
#include "IteratorTest.h"

#include <algorithm>
#include <vector>

using namespace std;

void IteratorTest::doit()
{
	//ָ�������
	//����������
	vector<int> intVector(100);
	intVector[21] = 50;
	vector<int>::iterator intIter = find(intVector.begin(), intVector.end(), 50);
	//����������

	//���������
	//���������
	double darray[10] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9 };
	vector<double> vDouble;
	vector<double>::iterator outputIterator = vDouble.begin();
	copy(darray, darray+10, outputIterator);	//��������
	while (outputIterator != vDouble.end()){
		outputIterator++;
	}
	//ǰ�Ƶ�����
	replace(vDouble.begin(), vDouble.end(), 1.1, 3.1415926);	//����Χ��1.1�滻Ϊ3.1415926
	//˫�������
	reverse(vDouble.begin(), vDouble.end());
	//������ʵ�����
	random_shuffle(vDouble.begin(), vDouble.end());
}
