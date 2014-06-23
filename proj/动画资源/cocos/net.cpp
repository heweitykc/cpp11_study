#include "net.h"
#include "events.h"

static NetLayer* instance = nullptr;

NetLayer* NetLayer::getInstance()
{
	if (!instance){
		instance = new NetLayer();
		instance->init();
	}
	return instance;
}

NetLayer::NetLayer()
{
	dispatcher.setEnabled(true);
}

NetLayer::~NetLayer()
{
	
}

void NetLayer::init()
{

}

void NetLayer::connect()
{
	network::WebSocket::State state = _wsi.getReadyState();
	if (state == network::WebSocket::State::OPEN) return;

	_wsi.init(*this, "ws://192.168.0.106:8080");
	log("connecting");
}

void NetLayer::close()
{
	log("close");
	network::WebSocket::State state = _wsi.getReadyState();
	if (state == network::WebSocket::State::OPEN){
		_wsi.close();
	}
}

void printRaw(unsigned char* data, int len)
{
	int i = 0;
	printf("raw:");
	while (i < len){
		log("%x ", data[i++]);
	}
}

void NetLayer::clientLogin()
{
	netpack pack;
	pack.cmd = pkgUtil::NetProtocol::login;
	pack.len = 0;
	send(pack);
}

void NetLayer::clientMove(int x, int y)
{
	netpack pack;
	pack.cmd = pkgUtil::NetProtocol::mvrole;
	pack.len = 8;
	pack.raw = new unsigned char[8];
	pkgUtil::fillInt(pack.raw, 0, x);
	pkgUtil::fillInt(pack.raw, 4, y);
	send(pack);
}

void NetLayer::onOpen(cocos2d::network::WebSocket* ws)
{
	log("onOpen ");
	clientLogin();
}

void NetLayer::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	netpack pack;
	pkgUtil::unpkg((unsigned char*)data.bytes,&pack);

	if (pack.cmd == pkgUtil::NetProtocol::login){
		_uid = pkgUtil::getInt(pack.raw, 0);
		log("login uid=%d", _uid);

		dispatcher.dispatchCustomEvent(NET_LOGIN);
	} else if (pack.cmd == pkgUtil::NetProtocol::addrole){
		Add_Role addrole;
		addrole.uid = pkgUtil::getInt(pack.raw, 0);
		addrole.x = pkgUtil::getInt(pack.raw, 4);
		addrole.y = pkgUtil::getInt(pack.raw, 8);
		addrole.isHero = (_uid == addrole.uid);
		log("addrole=%d,x=%d,y=%d", addrole.uid, addrole.x, addrole.y);

		dispatcher.dispatchCustomEvent(NET_ADDROLE, &addrole);
	}
}

void NetLayer::onClose(cocos2d::network::WebSocket* ws)
{
	log("onClose ");
	_wsi.close();
}

void NetLayer::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
	log("onError ");
}

void NetLayer::send(netpack& pack)
{
	unsigned char *out = new unsigned char[pack.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&pack, out);
	printRaw(out, pack.len + pkgUtil::HEAD_SIZE);
	_wsi.send((unsigned char*)out, pack.len + pkgUtil::HEAD_SIZE);
	delete[] out;
}