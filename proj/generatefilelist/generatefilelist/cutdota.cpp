#include "stdafx.h"

using namespace std;

void cutfile()
{
	ifstream is("AM.fca", std::ifstream::binary);
	if (is){
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		string str;
		str.resize(length,' ');
		char* begin = &*str.begin();

		is.read(begin, length);
		is.close();

		int idx = str.find("PK");
		while (idx >= 0){
			cout << "idx:" << idx << endl;
			idx = str.find("PK",idx+1);
		}		
	}
}