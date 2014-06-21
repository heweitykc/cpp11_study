#ifndef __PKG_UTIL_H__
#define __PKG_UTIL_H__

#define BUFFSIZE 8192
#include <vector>

/*
1001(login)	->{}   <-{uid}
2(addrole) <<-{uid}
3(rmrole)  <<-{uid}
4(mvrole)  ->{x,y}	<<-{uid,x,y}
5
6
7
*/

struct netpack{
	unsigned int len;			//����
	unsigned int cmd;		//Э���
	unsigned char* raw;		//����
};

class pkgUtil
{
public:
	static const int HEAD_SIZE = 8;
	static void printRaw(unsigned char* data, int len);
	static void pkg(netpack *pack, unsigned char* out);						//���
	static void unpkg(const char* in, netpack *pack);			//���

	pkgUtil();
	void append(const char* str, int len);
	void getNext(netpack* pack);
private:
	int _cursor;
	char _buff[BUFFSIZE];
};

#endif