#include "world.h"
#include <algorithm>

world::world()
{
	_cnt = 1000;
}

Role* world::add(Poco::Net::WebSocket *sock)
{
	_cnt++;
	Role *role = new Role();
	role->model.uid = _cnt;
	role->model.x = 0;
	role->model.y = 0;
	role->sock = sock;
	_list.push_back(role);
	std::cout << role->model.uid << "  entered, current=" << _list.size() << std::endl;
	return role;
}

void world::rm(Poco::Net::WebSocket* ws)
{
	std::vector<Role*>::iterator itr = std::find_if(
		_list.begin(),
		_list.end(), [&](Role* role){ return role->sock == ws; }
	);
	std::cout << "closed uid =" << (*itr)->model.uid << std::endl;

	_list.erase(std::remove_if(_list.begin(), 
										_list.end(),
										[&](Role* role){return role->sock == ws;}
	), _list.end());
}

void world::loop()
{
	netpack pack;
	pack.cmd = pkgUtil::NetProtocol::beat;
	pack.len = 0;
	pack.raw = new unsigned char[pack.len];
	unsigned char *out = new unsigned char[pack.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&pack, out);

	for each (Role* role in _list){
		if (role->sock->available()){
			role->sock->sendFrame(out, pack.len + pkgUtil::HEAD_SIZE);
		}
	}
	delete[] out;
}

std::vector<Role*> world::getList()
{
	return _list;
}