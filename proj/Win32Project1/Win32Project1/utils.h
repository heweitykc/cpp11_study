#pragma once

void disp(HWND hwnd, const TCHAR* str);
void disp(HWND hwnd, const char* str);
void clear();

class WinNode{
public:
	HWND hWnd;
};