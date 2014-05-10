#include "stdafx.h"
#include "rtti.h"
#include "vector.h"

void TV::goChannel(int channel)
{
	TCHAR msg[256];
	ZeroMemory(msg, 256);
	StringCbPrintf(msg, 256, L"您选择了频道%d。", channel);
	disp(this->hWnd, msg);
}

void YJTV::sayYJ()
{
	disp(this->hWnd, "i'm yjtv");
}

void CRTTV::sayCRT()
{
	disp(this->hWnd, "i'm crttv");
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
	disp(hWnd, typeid(*base).name());
	disp(hWnd, typeid(YJTV).name());
	disp(hWnd, typeid(CRTTV).name());

}

void RTTITest::test()
{
	YJTV* yjtv = new YJTV;
	CRTTV* crttv = new CRTTV;
	TV* tv0 = yjtv;
	yjtv->hWnd = this->hWnd;
	crttv->hWnd = this->hWnd;
	tv0->goChannel(100);

	showWho(yjtv,hWnd);
	showWho(crttv,hWnd);


	GEOM::Vector vector1(1.01, 1.02, 'a');
	GEOM::Vector vector2(2.01, 9.02, 'b');
	GEOM::Vector v3 = vector1 + vector2;

	TCHAR msg[256];
	ZeroMemory(msg, 256);
	StringCbPrintf(msg, 256, L"相加的结果x=%4.2f,y=%4.2f。", v3.get_x(), v3.get_y());
	disp(hWnd, msg);

	delete yjtv;
}