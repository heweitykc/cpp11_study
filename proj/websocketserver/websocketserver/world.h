#ifndef __WORLD_H__
#define __WORLD_H__

#include "Poco/Net/WebSocket.h"
#include <vector>
#include "pkgutil.h"

struct Role{
	RoleModel model;
	Poco::Net::WebSocket *sock;
};

class world
{
public:
	world();
	std::vector<Role*> getList();
	Role* add(Poco::Net::WebSocket *sock);
	void loop();
	void rm(Poco::Net::WebSocket* ws);
private:
	std::vector<Role*> _list;
	unsigned int _cnt;
};
#endif