#ifndef __PKG_UTIL_H__
#define __PKG_UTIL_H__

#define BUFFSIZE 1024*1024
#include <vector>

struct netpack{
	int len;		//����
	int cmd;		//Э���
	char* raw;		//����
};

class pkgUtil
{
public:
	static const int HEAD_SIZE = 8;
	static void printRaw(char* data, int len);
	static void pkg(netpack *pack, char* out);					//���
	static void unpkg(const char* in, netpack *pack);			//���

	pkgUtil();
	void append(const char* str, int len);
	void getNext(netpack* pack);
private:
	int _beginCursor;		//��Ч���ݵĿ�ʼλ��
	int _endCursor;			//��Ч���ݵĽ���λ��
	char _buff0[BUFFSIZE];	//��buffer

	void resetBuffer();		//���ÿ�ʼλ��Ϊ0
	char _buff1[BUFFSIZE];  //����ʱ�ĸ���buffer
};

#endif