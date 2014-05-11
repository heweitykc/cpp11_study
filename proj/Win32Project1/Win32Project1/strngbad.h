#pragma once
#include "stdafx.h"

class StringBad
{
private:
	char *str;
	int len;
	HWND _hWnd;
	static int num_strings;
public:
	StringBad(const char *s, HWND hWnd);
	StringBad();
	~StringBad();
	friend std::ostream &operator<<(std::ostream &os, const StringBad &st);
};