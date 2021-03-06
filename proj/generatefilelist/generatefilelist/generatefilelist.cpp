// generatefilelist.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

TCHAR root[] = L"D:\\workspace\\WindofKindom\\Source\\Client\\Release";
TCHAR rroot[] = L"D:\\workspace\\WindofKindom\\Source\\Client\\Release\\";
map<wstring, wstring> allpath;

void TraverseFolder(LPCTSTR lpPath);
void printall();
void cutfile();

void  fileTimeToTime_t(FILETIME  ft, time_t  *t)
{
	LONGLONG  ll;

	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;

	ll = ((LONGLONG)ft.dwHighDateTime << 32) + ft.dwLowDateTime;

	*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

wstring& replace_all(wstring&  str, const wstring&  old_value, const wstring&   new_value)
{
	for (wstring::size_type pos(0); pos != wstring::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != wstring::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return str;
}

/*
int _tmain(int argc, _TCHAR* argv[])
{
	TraverseFolder(root);
	printall();
	printf("ver ok!");
	return 0;
}
*/


//遍历文件夹函数
void TraverseFolder(LPCTSTR lpPath)
{
	TCHAR szFind[MAX_PATH] = { _T("\0") };
	WIN32_FIND_DATA findFileData;
	BOOL bRet;

	_tcscpy_s(szFind, MAX_PATH, lpPath);
	_tcscat_s(szFind, _T("\\*.*"));     //这里一定要指明通配符，不然不会读取所有文件和目录

	HANDLE hFind = ::FindFirstFile(szFind, &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	//遍历文件夹
	while (TRUE)
	{
		if (findFileData.cFileName[0] != _T('.'))
		{//不是当前路径或者父目录的快捷方式
			TCHAR keystr[1024] = {_T("\0")};
			TCHAR valuestr[1024] = { _T("\0") };

			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//这是一个普通目录
				//设置下一个将要扫描的文件夹路径
				_tcscpy_s(szFind, MAX_PATH, lpPath);
				_tcscat_s(szFind, _T("\\"));
				_tcscat_s(szFind, findFileData.cFileName);
				//遍历该目录
				TraverseFolder(szFind);
			} else {
				wsprintf(keystr, _T("%s\\%s"), lpPath, findFileData.cFileName);
				time_t ttime;
				fileTimeToTime_t(findFileData.ftLastWriteTime, &ttime);
				wsprintf(valuestr, _T("%I64d"), ttime);
				allpath[wstring(keystr)] = wstring(valuestr);
			}
		}
		//如果是当前路径或者父目录的快捷方式，或者是普通目录，则寻找下一个目录或者文件
		bRet = ::FindNextFile(hFind, &findFileData);
		if (!bRet)
		{//函数调用失败
			//cout << "FindNextFile failed, error code: " 
			//  << GetLastError() << endl;
			break;
		}
	}

	::FindClose(hFind);
}

void printall()
{
	locale &loc = locale::global(locale(locale(), "", LC_CTYPE));
	wofstream outfile("log.txt", ofstream::binary);
	
	map<wstring, wstring>::iterator ite = allpath.begin();
	for (; ite != allpath.end(); ++ite){
		wstring path;
		path.append(ite->first.c_str());
		path.append(_T("="));
		path.append(ite->second.c_str());
		path.append(_T("\n"));
		replace_all(path, rroot, _T(""));
		replace_all(path, _T("\\"), _T("/"));
		const wchar_t *pathstr = path.c_str();
		outfile.write(pathstr, wcslen(pathstr));
	}
}
