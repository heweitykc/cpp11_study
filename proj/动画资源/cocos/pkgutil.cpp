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

void pkgUtil::pkg(netpack *pack, unsigned char* out)
{
	int intVar = pack->len;
	out[3] = intVar & 0xff;
	out[2] = (intVar & 0xff00)>>8;
	out[1] = (intVar & 0xff0000)>>16;
	out[0] = (intVar & 0xff000000)>>24;

	intVar = pack->cmd;
	out[7] = intVar & 0xff;
	out[6] = (intVar & 0xff00)>>8;
	out[5] = (intVar & 0xff0000) >> 16;
	out[4] = (intVar & 0xff000000) >> 24;

	unsigned int i = 0;
	while (i < pack->len){
		out[i + pkgUtil::HEAD_SIZE] = pack->raw[i];
		i++;
	}
}

void pkgUtil::unpkg(const char* in, netpack *pack)
{
	int len = (*(in + 3)) + ((*(in + 2)) << 8) + ((*(in + 1)) << 16) + ((*in) << 24);
	int cmd = (unsigned char)(*(in + 7)) + ((unsigned char)(*(in + 6)) << 8) + ((unsigned char)(*(in + 5)) << 16) + ((unsigned char)(*(in + 4)) << 24);
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