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
	netpack in;
	in.raw = "abc";
	in.cmd = 100;
	in.len = sizeof(in.raw)-1;
	char *out = new char[in.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&in, out);
	pkgUtil::printRaw(out, in.len + pkgUtil::HEAD_SIZE);
	
	netpack out2;
	pkgUtil::unpkg(out, &out2);
	pkgUtil::printRaw(out2.raw, out2.len);

	pkgUtil util;
	util.append(out, in.len + pkgUtil::HEAD_SIZE);

	netpack pack;
	util.getNext(&pack);
	if (pack.cmd > 0)
		printf("%d,%d,%s", pack.len, pack.cmd,pack.raw);
	int len = 0;
	scanf_s("%d",len);

	delete[] out;
	return 0;
}

