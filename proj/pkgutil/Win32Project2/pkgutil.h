#ifndef __PKG_UTIL_H__
#define __PKG_UTIL_H__

#define BUFFSIZE 8192
#include <vector>

struct netpack{
	int len;			//����
	int cmd;		//Э���
	char* raw;		//����
};

class pkgUtil
{
public:
	static const int HEAD_SIZE = 8;
	static void printRaw(char* data, int len);
	static void pkg(netpack *pack, char* out);						//���
	static void unpkg(const char* in, netpack *pack);			//���

	pkgUtil();
	void append(const char* str, int len);
	void getNext(netpack* pack);
private:
	int _cursor;
	char _buff[BUFFSIZE];
};

#endif