#include "stdafx.h"

const wchar_t TRI[] = { L"triangles" };
const wchar_t NODES[] = { L"nodes" };
const wchar_t SKELETON[] = {L"skeleton" };
const wchar_t END[] = { L"end" };

void readBlock(std::wifstream& fs, const wchar_t* sign, int len)
{
	wchar_t buff[1024];
	memset(buff, 0, 1024);
	int cnt = 0;
	while (fs.getline(buff, 1024)){
		if (std::wcsncmp(buff, END, sizeof(END)) == 0){
			std::wcout << "=" << cnt << std::endl;
			break;
		}
		//std::wcout << "buff£º" << buff << std::endl;
		//memset(buff, 0, 1024);
		cnt++;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::wifstream  fs;
	std::wcout << "input file:" << argv[1] << std::endl;
	fs.open(argv[1]);	

	wchar_t buff[1024];
	memset(buff, 0, 1024);

	while (fs.getline(buff, 1024)){
		const wchar_t *sign;
		int len;
		if (std::wcsncmp(buff, NODES, sizeof(NODES)) == 0){
			sign = NODES;
			len = sizeof(NODES);
		} else if (std::wcsncmp(buff, SKELETON, sizeof(SKELETON)) == 0){
			sign = SKELETON;
			len = sizeof(SKELETON);
		} else if (std::wcsncmp(buff, TRI, sizeof(TRI)) == 0){
			sign = TRI;
			len = sizeof(TRI);
		}
		readBlock(fs, sign, len);
	}

	fs.close();

	int i;
	std::cin >> i;
	return 0;
}