#include "pkgutil.h"
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

void pkgUtil::fillInt(unsigned char* in, int pos, unsigned int intVar)
{
	in[pos + 3] = intVar & 0xff;
	in[pos + 2] = (intVar & 0xff00) >> 8;
	in[pos + 1] = (intVar & 0xff0000) >> 16;
	in[pos] = (intVar & 0xff000000) >> 24;
}

unsigned int pkgUtil::getInt(const unsigned char* in, int pos)
{
	return (unsigned char)(*(in + pos + 3)) 
		+ ((unsigned char)(*(in + pos + 2)) << 8) 
		+ ((unsigned char)(*(in + pos + 1)) << 16) 
		+ ((unsigned char)(*(in + pos)) << 16);
}

void pkgUtil::pkg(netpack *pack, unsigned char* out)
{
	fillInt(out, 0, pack->len);
	fillInt(out, 4, pack->cmd);

	unsigned int i = 0;
	while (i < pack->len){
		out[i + pkgUtil::HEAD_SIZE] = pack->raw[i];
		i++;
	}
}

void pkgUtil::unpkg(const unsigned char* in, netpack *pack)
{
	int len = getInt(in, 0);
	int cmd = getInt(in, 4);
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