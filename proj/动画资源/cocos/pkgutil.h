#ifndef __PKG_UTIL_H__
#define __PKG_UTIL_H__

#define BUFFSIZE 8192
#include <vector>

/*
1001(login)	->{}   <-{uid}
1002(addrole) <<-{uid}
1003(rmrole)  <<-{uid}
1004(mvrole)  ->{x,y}	<<-{uid,x,y}
5
6
7
*/

struct netpack{
	unsigned int len;			//长度
	unsigned int cmd;		//协议号
	unsigned char* raw;		//数据
};

struct RoleModel
{
	int uid;
	std::string name;
	float x;
	float y;
};

class pkgUtil
{
public:
	static enum NetProtocol{ login=1001, addrole=1002, rmrole=1003,mvrole=1004, beat=100000  };
	static const int HEAD_SIZE = 8;
	static void printRaw(unsigned char* data, int len);
	static void pkg(netpack *pack, unsigned char* out);						//封包
	static void unpkg(const char* in, netpack *pack);			//解包

	pkgUtil();
	void append(const char* str, int len);
	void getNext(netpack* pack);
private:
	int _cursor;
	char _buff[BUFFSIZE];
};

#endif