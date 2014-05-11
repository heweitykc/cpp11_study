#include "stdafx.h"
#include "strngbad.h"
#include "utils.h"

using std::cout;

int StringBad::num_strings = 0;

StringBad::StringBad(const char *s, HWND hWnd)
{
	_hWnd = hWnd;
	len = std::strlen(s);
	str = new char[len+1];
	std::strcpy(str,s);
	num_strings++;
	dispW(hWnd, TEXT("%d: object created"), num_strings);
}

