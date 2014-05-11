#pragma once

void dispW(HWND hwnd, const TCHAR* str, ...);
void dispA(HWND hwnd, const char* str, ...);

void clear();

class WinNode{
public:
	HWND hWnd;
};