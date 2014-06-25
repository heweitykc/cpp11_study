#include "pkgutil.h"
#include "binarytool.h"

#include <iostream>

using namespace std;

void pkgUtil::printRaw(unsigned char* data, int len)
{
	int i = 0;
	printf("raw:");
	while (i < len){
		printf("%x ", data[i++]);
	}
	printf("\n");
}

void pkgUtil::pkg(netpack *pack, unsigned char* out)
{
	BinaryTool::fillInt(out, 0, pack->len);
	BinaryTool::fillInt(out, 4, pack->cmd);

	unsigned int i = 0;
	while (i < pack->len){
		out[i + pkgUtil::HEAD_SIZE] = pack->raw[i];
		i++;
	}
}

void pkgUtil::unpkg(const unsigned char* in, netpack *pack)
{
	int len = BinaryTool::getInt(in, 0);
	int cmd = BinaryTool::getInt(in, 4);
	pack->raw = new unsigned char[len];
	pack->len = len;
	pack->cmd = cmd;
	int i = 0;
	while (i < len){
		pack->raw[i] = in[i + pkgUtil::HEAD_SIZE];
		i++;
	}
}

pkgUtil::pkgUtil()
{
	std::memset(_buff, 0, BUFFSIZE);
	_cursor = 0;
}

void pkgUtil::append(const char* str, int len)
{
	int i = 0;
	while (i++ < len){
		_buff[_cursor] = str[i];
		_cursor++;
	}
}

void pkgUtil::getNext(netpack* pack)
{
	pack->cmd = -1;

}