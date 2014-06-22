#ifndef __NET_HANDLER_H__
#define __NET_HANDLER__

#include "pkgutil.h"
#include "world.h"
#include "Poco/Net/WebSocket.h"

class netHandler
{
public:
	netHandler(world &world);
	void excute(unsigned char* buffer, Poco::Net::WebSocket* ws, int flags);
	void close(Poco::Net::WebSocket* ws);
private:
	world _world;

	void send(Poco::Net::WebSocket* ws, netpack& pack, int flag);
	void login(Poco::Net::WebSocket* ws, Role* role, int flag);
	void syncWorld(Poco::Net::WebSocket* ws, int flag);
	void syncRole(Poco::Net::WebSocket* ws, Role* role, int flag);
};

#endif