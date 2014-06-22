
#include "netHandler.h"
#include <iostream>

using namespace std;
using namespace Poco::Net;

netHandler::netHandler(world &world)
{
	_world = world;
}

void netHandler::excute(unsigned char* buffer, WebSocket* ws, int flag)
{
	netpack pkg;
	pkgUtil::unpkg(buffer, &pkg);
	cout << "in cmd:" << pkg.cmd << "   msg:" << pkg.raw << endl;

	if (pkg.cmd == pkgUtil::NetProtocol::login){
		Role* role = _world.add(ws);
		login(ws, role, flag);
		syncWorld(ws, flag);
	}
}

void netHandler::syncWorld(Poco::Net::WebSocket* ws, int flag)
{
	vector<Role*> list = _world.getList();
	for each (Role* role in list){
		syncRole(ws, role, flag);
	}
}

void netHandler::syncRole(Poco::Net::WebSocket* ws, Role* role, int flag)
{
	netpack pack;
	pack.cmd = pkgUtil::NetProtocol::addrole;
	pack.len = 12;
	pack.raw = new unsigned char[12];
	pkgUtil::fillInt(pack.raw, 0, role->model.uid);
	pkgUtil::fillInt(pack.raw, 4, role->model.x);
	pkgUtil::fillInt(pack.raw, 8, role->model.y);
	send(ws, pack, flag);
}

void netHandler::login(Poco::Net::WebSocket* ws, Role* role, int flag)
{
	netpack pack;
	pack.cmd = pkgUtil::NetProtocol::login;
	pack.len = 4;
	pack.raw = new unsigned char[4];
	pkgUtil::fillInt(pack.raw, 0, role->model.uid);
	send(ws, pack, flag);
}

void netHandler::send(Poco::Net::WebSocket* ws, netpack& pack, int flag)
{
	unsigned char *out = new unsigned char[pack.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&pack, out);
	ws->sendFrame(out, pack.len + pkgUtil::HEAD_SIZE, flag);
	delete[] out;
}

void netHandler::close(Poco::Net::WebSocket* ws)
{
	_world.rm(ws);
}