#include "stdafx.h"
#include "pkgutil.h"
#include <iostream>

using namespace std;


void pkgUtil::printRaw(char* data, int len)
{
	int i = 0;
	printf("raw:");
	while (i < len){
		printf("%x ", data[i++]);
	}
	printf("\n");
}

void pkgUtil::pkg(netpack *pack, char* out)
{
	char* cp = (char*)&(pack->len);
	out[3] = *cp;
	out[2] = *(cp + 1);
	out[1] = *(cp + 2);
	out[0] = *(cp + 3);

	cp = (char*)&(pack->cmd);
	out[7] = *cp;
	out[6] = *(cp + 1);
	out[5] = *(cp + 2);
	out[4] = *(cp + 3);

	int i = 0;
	while (i < pack->len){
		out[i + pkgUtil::HEAD_SIZE] = pack->raw[i];
		i++;
	}
}

void pkgUtil::unpkg(const char* in, netpack *pack)
{
	int len = (*(in + 3)) + ((*(in + 2)) << 8) + ((*(in + 1)) << 16) + ((*in) << 24);
	int cmd = (*(in + 7)) + ((*(in + 6)) << 8) + ((*(in + 5)) << 16) + ((*(in+4)) << 24);
	pack->raw = new char[len];
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