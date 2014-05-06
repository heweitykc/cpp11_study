#include "stdafx.h"
#include "utils.h"

static int text_cnt = 0;

void disp(HWND hwnd, const TCHAR* str)
{
	HFONT hfont, hOldfont;
	HDC hdc;

	hfont = (HFONT)GetStockObject(SYSTEM_FONT);
	hdc = GetDC(hwnd);
	hOldfont = (HFONT)SelectObject(hdc, hfont);
	if (hOldfont){
		TextOutW(hdc, 5, text_cnt * 20, str, lstrlenW(str));
		SelectObject(hdc, hOldfont);
	}
	ReleaseDC(hwnd, hdc);
	text_cnt++;
}

void disp(HWND hwnd, const char* str)
{
	HFONT hfont, hOldfont;
	HDC hdc;

	hfont = (HFONT)GetStockObject(SYSTEM_FONT);
	hdc = GetDC(hwnd);
	hOldfont = (HFONT)SelectObject(hdc, hfont);
	if (hOldfont){
		TextOutA(hdc, 5, text_cnt * 20, str, strlen(str));
		SelectObject(hdc, hOldfont);
	}
	ReleaseDC(hwnd, hdc);
	text_cnt++;
}

void clear()
{
	text_cnt = 0;
}