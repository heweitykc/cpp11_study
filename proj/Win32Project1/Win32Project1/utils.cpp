#include "stdafx.h"
#include "utils.h"

#define TXTCOUNT 2048
static int text_cnt = 0;
static TCHAR msg[TXTCOUNT];
static char cmsg[TXTCOUNT];

void dispW(HWND hwnd, const TCHAR* str, ...)
{
	va_list args;
	va_start(args, str);

	ZeroMemory(msg, TXTCOUNT);
	StringCchPrintf(msg, TXTCOUNT, str, args);
	va_end(args);

	HFONT hfont, hOldfont;
	HDC hdc;

	hfont = (HFONT)GetStockObject(SYSTEM_FONT);
	hdc = GetDC(hwnd);
	hOldfont = (HFONT)SelectObject(hdc, hfont);
	if (hOldfont){
		TextOutW(hdc, 5, text_cnt * 20, msg, lstrlenW(msg));
		SelectObject(hdc, hOldfont);
	}
	ReleaseDC(hwnd, hdc);
	text_cnt++;
}

void dispA(HWND hwnd, const char* str, ...)
{
	va_list args;
	va_start(args, str);

	ZeroMemory(cmsg, TXTCOUNT);
	sprintf(cmsg, str, args);
	va_end(args);

	HFONT hfont, hOldfont;
	HDC hdc;

	hfont = (HFONT)GetStockObject(SYSTEM_FONT);
	hdc = GetDC(hwnd);
	hOldfont = (HFONT)SelectObject(hdc, hfont);
	if (hOldfont){
		TextOutA(hdc, 5, text_cnt * 20, cmsg, strlen(cmsg));
		SelectObject(hdc, hOldfont);
	}
	ReleaseDC(hwnd, hdc);
	text_cnt++;
}

void clear()
{
	text_cnt = 0;
}