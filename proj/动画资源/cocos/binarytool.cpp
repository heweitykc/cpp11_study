#include "binarytool.h"

void BinaryTool::fillInt(unsigned char* in, int pos, unsigned int intVar)
{
	in[pos + 3] = intVar & 0xff;
	in[pos + 2] = (intVar & 0xff00) >> 8;
	in[pos + 1] = (intVar & 0xff0000) >> 16;
	in[pos] = (intVar & 0xff000000) >> 24;
}

unsigned int BinaryTool::getInt(const unsigned char* in, int pos)
{
	return (unsigned char)(*(in + pos + 3))
		+ ((unsigned char)(*(in + pos + 2)) << 8)
		+ ((unsigned char)(*(in + pos + 1)) << 16)
		+ ((unsigned char)(*(in + pos)) << 16);
}