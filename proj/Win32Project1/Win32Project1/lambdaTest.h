#pragma once
#include "win32base.h"

class LambdaTest : public win32base
{
public:
	LambdaTest(HWND hWnd, int a);
	void dotest();
private:
	int _a;
};
