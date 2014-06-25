#ifndef __BINARY_TOOL_H__
#define __BINARY_TOOL_H__

class BinaryTool{
public:
	static void fillInt(unsigned char* in, int pos, unsigned int intVar);
	static unsigned int getInt(const unsigned char* in, int pos);

};

#endif