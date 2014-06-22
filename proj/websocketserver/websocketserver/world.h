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
	Role* add(Poco::Net::WebSocket *sock);
	void loop();
	void rm(Role* role);
private:
	std::vector<Role*> _list;
	unsigned int _cnt;
};
#endif