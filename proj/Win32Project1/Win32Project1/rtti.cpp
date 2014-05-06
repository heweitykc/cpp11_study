#include "stdafx.h"
#include "rtti.h"

void TV::goChannel(int channel)
{
	TCHAR msg[256];
	ZeroMemory(msg, 256);
	wsprintf(msg, L"ÄúÑ¡ÔñÁËÆµµÀ%d¡£", channel);
	disp(this->hWnd, msg);
}

void RTTITest::test()
{
	YJTV* yjtv = new YJTV;
	TV* tv0 = yjtv;
	yjtv->hWnd = this->hWnd;
	//tv.goChannel(100);

	disp(this->hWnd, typeid(yjtv).name());
	disp(this->hWnd, typeid(tv0).name());
	delete yjtv;
}