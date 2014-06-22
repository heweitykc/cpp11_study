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
	role->sock = sock;
	_list.push_back(role);
	std::cout << role->model.uid << "  entered" << std::endl;
	return role;
}

void world::rm(Role* role)
{
	std::cout << role->model.uid << "   closed" << std::endl;
	std::remove(_list.begin(), _list.end(), role);
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