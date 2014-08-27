// pkgutiltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pkgutil.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{	
	pkgUtil* util = new pkgUtil();

	netpack in;
	in.raw = "abc";
	in.cmd = 100;
	in.len = strlen(in.raw);

	netpack in2;
	in2.raw = "a";
	in2.cmd = 104;
	in2.len = strlen(in2.raw);

	netpack in3;
	in3.raw = "abcsfcdsf";
	in3.cmd = 102;
	in3.len = strlen(in3.raw);

	char *out = new char[in.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&in, out);
	util->append(out, in.len + pkgUtil::HEAD_SIZE);
	delete[] out;

	out = new char[in2.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&in2, out);
	util->append(out, in2.len + pkgUtil::HEAD_SIZE);
	delete[] out;

	out = new char[in3.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&in3, out);
	util->append(out, in3.len + pkgUtil::HEAD_SIZE);
	delete[] out;
	
	//解包
	netpack pack;
	util->getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd,pack.raw);
	util->getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd, pack.raw);
	util->getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd, pack.raw);
	util->getNext(&pack);

	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd, pack.raw);
	util->getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd, pack.raw);
	util->getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s,\n", pack.len, pack.cmd, pack.raw);
	util->getNext(&pack);

	int len = 0;
	scanf_s("%d",len);
	
	delete util;
	return 0;
}

