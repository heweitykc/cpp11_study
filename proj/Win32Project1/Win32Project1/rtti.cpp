#include "stdafx.h"
#include "rtti.h"
#include "vector.h"
#include "strngbad.h"
#include "lambdaTest.h"
#include <algorithm>
#include <vector>

void TV::goChannel(int channel)
{

	dispW(this->hWnd, TEXT("您 slelect %d。"), channel);
}

void YJTV::sayYJ()
{
	dispW(this->hWnd, L"i'm yjtv");
}

void CRTTV::sayCRT()
{
	dispW(this->hWnd, L"i'm crttv");
}

void showWho(TV *base, const HWND& hWnd) {
	if (typeid(*base) == typeid(YJTV)) {
		YJTV *derived1 = static_cast<YJTV*>(base);
		derived1->sayYJ();
	}
	else if (typeid(*base) == typeid(CRTTV)) {
		CRTTV *derived2 = static_cast<CRTTV*>(base);
		derived2->sayCRT();
	}
	const char* sname = typeid(*base).name();
	dispA(hWnd, "name is %s.", sname);
}

void RTTITest::test()
{
	YJTV* yjtv = new YJTV;
	CRTTV* crttv = new CRTTV;
	TV* tv0 = yjtv;
	yjtv->hWnd = this->hWnd;
	crttv->hWnd = this->hWnd;
	tv0->goChannel(110);

	showWho(yjtv,hWnd);
	showWho(crttv,hWnd);

	GEOM::Vector vector1(1.01, 1.02, 'a');
	GEOM::Vector vector2(2.01, 9.02, 'b');
	GEOM::Vector v3 = vector1 + vector2;

	dispW(hWnd, TEXT("相加的结果x=%4.2f,y=%4.2f。"), v3.get_x(), v3.get_y());

	auto badstr = new StringBad("good!",hWnd);

	LambdaTest lambdaTest(hWnd, 100);
	lambdaTest.dotest();

	int iarray[100] = {0};
	iarray[0] = 101;
	iarray[10] = 1012;
	iarray[61] = 102;
	int* ip = std::find(iarray, iarray+100, 1012);
	if (ip == iarray + 100){
		dispW(hWnd, L"没找到");
	} else {
		dispW(hWnd, L"iarray=%x, 找到了%x", iarray, ip);
	}

	std::vector<int> intVector(100);
	intVector[12] = 1001;
	std::vector<int>::iterator inIter = find(intVector.begin(), intVector.end(), 1001);
	if (inIter != intVector.end()){
		dispW(hWnd, L"intVector=%x, 找到了%d", intVector, *inIter);
	}
	else {
		dispW(hWnd, L"没找到");
	}
	delete yjtv;
}