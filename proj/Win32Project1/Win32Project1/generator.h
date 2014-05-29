#pragma once
#include "stdafx.h"
#include "win32base.h"

using namespace std;

class generator : public win32base
{
public:
	void doit();
};

void Display(vector<int>& v, const char* s);
void Display(list<int>& v, const char* s);