#include "stdafx.h"
#include "lambdaTest.h"
#include "utils.h"

using namespace std;

LambdaTest::LambdaTest(HWND hWnd, int a) : win32base(hWnd), _a(a)
{
	_a += 100;
}

void LambdaTest::dotest()
{
	auto func = [] (HWND hwnd) {
		dispA(hwnd, "good day! lambda!");
	};
	func(_hWnd);
}