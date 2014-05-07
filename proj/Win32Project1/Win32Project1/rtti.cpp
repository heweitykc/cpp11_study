#include "stdafx.h"
#include "rtti.h"

void TV::goChannel(int channel)
{
	TCHAR msg[256];
	ZeroMemory(msg, 256);
	wsprintf(msg, L"ÄúÑ¡ÔñÁËÆµµÀ%d¡£", channel);
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

	delete yjtv;
}