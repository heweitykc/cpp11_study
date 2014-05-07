#pragma once

#include "utils.h"

class TV : public WinNode
{
public:
	int lsound;
	int rsound;
	void goChannel(int channel);
};

class YJTV : public TV{
public:
	void sayYJ();
};

class CRTTV : public TV{
public:
	void sayCRT();
};

class RTTITest : public WinNode{
public:
	void test();
};