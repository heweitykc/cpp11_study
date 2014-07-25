#include "stdafx.h"

const char TRI[] = { "triangles" };
const char NODES[] = { "nodes" };
const char SKELETON[] = {"skeleton" };
const char END[] = { "end" };

using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

int split(const string& str, vector<string>& ret_, string sep = " ")
{
	if (str.empty()){
		return 0;
	}

	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

map<string, list<float>*> vertexMap;
map<string, list<int>*> indexMap;

void insertVertex(const char* rawstr, list<float>* list)
{
	string wstr(rawstr);
	vector<string> splitlist;
	split(wstr, splitlist);
	vector<string>::iterator itr = splitlist.begin();
	list->push_back(1.0f);
	list->push_back(0.0f);
	list->push_back(0.0f);
	list->push_back(0.0f);

	list->push_back(stringToNum<float>(*itr));
	list->push_back(0.0f);
	list->push_back(0.0f);
	list->push_back(0.0f);

	itr++;
	while (itr != splitlist.end()){
		list->push_back(stringToNum<float>(*itr));
		itr++;
	}
}

void readVertices(std::ifstream& fs, const char* sign, int len)
{
	char buff[1024];
	int cnt = 0;	

	memset(buff, 0, 1024);
	while (fs.getline(buff, 1024)){
		if (std::strcmp(buff, END) == 0){
			std::wcout << "=" << cnt << std::endl;
			break;
		}
		string key(buff);
		if (vertexMap[key] == 0){
			//std::cout << "key=" << key << std::endl;
			vertexMap[key] = new list<float>();
		}
		
		memset(buff, 0, 1024);
		fs.getline(buff, 1024);	//v0
		insertVertex(buff, vertexMap[key]);

		memset(buff, 0, 1024);
		fs.getline(buff, 1024);	//v1
		insertVertex(buff, vertexMap[key]);

		memset(buff, 0, 1024);
		fs.getline(buff, 1024);	//v2
		insertVertex(buff, vertexMap[key]);

		memset(buff, 0, 1024);
		cnt++;
	}
}


int main(int argc, char* argv[])
{
	std::ifstream  fs;
	std::cout << "input file:" << argv[1] << std::endl;
	fs.open(argv[1]);	

	char buff[1024];
	memset(buff, 0, 1024);

	while (fs.getline(buff, 1024)){
		const char *sign;
		int len;
		if (std::strcmp(buff, NODES) == 0){
			sign = NODES;
			len = sizeof(NODES);
		} else if (std::strcmp(buff, SKELETON) == 0){
			sign = SKELETON;
			len = sizeof(SKELETON);			
		} else if (std::strcmp(buff, TRI) == 0){
			sign = TRI;
			len = sizeof(TRI);
			readVertices(fs, TRI, len);
		}
	}

	fs.close();

	locale &loc = locale::global(locale(locale(), "", LC_CTYPE));
	map<string, list<float>*>::iterator it;
	for (it = vertexMap.begin(); it != vertexMap.end(); ++it)
	{
		string key = it->first;
		list<float>* list = it->second;
		cout << "key=" << key << ", len=" << list->size() << endl;

		char nbuff[256] = { 0 };

		int llen = list->size();

		stringstream ss;

		ss << "{\n";
		ss << ("\"version\": \"1.2\",\n");
		ss << ("\"mesh\": [\n");
		ss << ("{\n");
		ss << ("\"version\": \"1.2\",\n");
		ss << ("\"attributes\": [\n");
		ss << ("{\n");
		ss << ("\"size\":   4, \n");
		ss << ("\"type\": \"GL_FLOAT\", \n");
		ss << ("\"attribute\": \"VERTEX_ATTRIB_BLEND_WEIGHT\"\n");
		ss << ("}, {\n");
		ss << ("\"size\":   4, \n");
		ss << ("\"type\": \"GL_FLOAT\", \n");
		ss << ("\"attribute\": \"VERTEX_ATTRIB_BLEND_INDEX\"\n");
		ss << ("}, {\n");
		ss << ("\"size\":   3, \n");
		ss << ("\"type\": \"GL_FLOAT\", \n");
		ss << ("\"attribute\": \"VERTEX_ATTRIB_POSITION\"\n");
		ss << ("}, {\n");
		ss << ("\"size\":   3, \n");
		ss << ("\"type\": \"GL_FLOAT\", \n");
		ss << ("\"attribute\": \"VERTEX_ATTRIB_NORMAL\"\n");
		ss << ("}, {\n");
		ss << ("\"size\":   2, \n");
		ss << ("\"type\": \"GL_FLOAT\", \n");
		ss << ("\"attribute\": \"VERTEX_ATTRIB_TEX_COORD\"\n");
		ss << ("}\n");
		ss << ("],\n");
		ss << ("\"body\": [\n");
		ss << ("{\n");
		ss << ("\"vertices\": [\n");

		while (list->size() > 0){
			float fn = list->front();
			ss << fn;
			if (list->size()>1)
				ss << ",";
			list->pop_front();
		}

		ss << ("],\n");
		ss << ("\"vertexsize\":");
		ss << llen;
		ss << (", \n");
		ss << ("\"indices\": [\n");
		int i = 0;
		while (i < llen){
			ss << i;
			if (i<llen-1)
				ss << ",";
			i++;
		}
		ss << ("],\n");
		ss << ("\"indexnum\":");
		ss << llen;
		ss << "\n";
		ss << ("}\n");
		ss << ("]\n");
		ss << ("}\n");
		ss << ("],\n");
		ss << ("\"material\": [\n");
		ss << ("{\n");
		ss << ("\"version\": \"1.2\",\n");
		ss << ("\"base\": [\n");
		ss << ("{\n");
		ss << ("\"filename\": \"");
		ss << key; ss << ("\"\n");
		ss << ("}\n");
		ss << ("]\n");
		ss << ("}\n");
		ss << ("],\n");

		ss << ("\"skin\": [\n");
			
		ss << ("],\n");


		ss << ("\"animation\": [\n");
		ss << ("\"animation\": [\n");	
		ss << ("]\n");

		ss << ("}\n");

		ofstream outfile(key+".c3t");
		string content;
		while (getline(ss, content)){
			outfile.write(content.c_str(), content.size());
			outfile.write("\n",1);
		}
		outfile.close();
	}

	int i;
	std::cin >> i;
	return 0;
}