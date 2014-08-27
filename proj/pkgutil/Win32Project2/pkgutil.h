#ifndef __PKG_UTIL_H__
#define __PKG_UTIL_H__

#define BUFFSIZE 1024*1024
#include <vector>

struct netpack{
	int len;		//长度
	int cmd;		//协议号
	char* raw;		//数据
};

class pkgUtil
{
public:
	static const int HEAD_SIZE = 8;
	static void printRaw(char* data, int len);
	static void pkg(netpack *pack, char* out);					//封包
	static void unpkg(const char* in, netpack *pack);			//解包

	pkgUtil();
	void append(const char* str, int len);
	void getNext(netpack* pack);
private:
	int _beginCursor;		//有效数据的开始位置
	int _endCursor;			//有效数据的结束位置
	char _buff0[BUFFSIZE];	//主buffer

	void resetBuffer();		//重置开始位置为0
	char _buff1[BUFFSIZE];  //重置时的辅助buffer
};

#endif