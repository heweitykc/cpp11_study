#include "net.h"
#include "pkgutil.h"

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

void NetLayer::send(std::string& msg, int cmd)
{
	log("send %s", msg.data());
	netpack pack;
	pack.len = msg.length();
	pack.cmd = cmd;
	pack.raw = new unsigned char[pack.len];
	memcpy(pack.raw, msg.data(), pack.len);

	unsigned char *out = new unsigned char[pack.len + pkgUtil::HEAD_SIZE];
	pkgUtil::pkg(&pack, out);
	printRaw(out, pack.len + pkgUtil::HEAD_SIZE);
	_wsi.send((unsigned char*)out, pack.len + pkgUtil::HEAD_SIZE);
	delete[] out;
}

void NetLayer::onOpen(cocos2d::network::WebSocket* ws)
{
	log("onOpen ");
	send(std::string("login"), pkgUtil::NetProtocol::login);
}

void NetLayer::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	netpack pack;
	pkgUtil::unpkg((unsigned char*)data.bytes,&pack);
	if (pack.cmd == pkgUtil::NetProtocol::login){
		_uid = pkgUtil::getInt(pack.raw, 0);
		log("login uid=%d", _uid);
	} else if (pack.cmd == pkgUtil::NetProtocol::addrole){
		int uid = pkgUtil::getInt(pack.raw, 0);
		int x = pkgUtil::getInt(pack.raw, 4);
		int y = pkgUtil::getInt(pack.raw, 8);
		log("addrole=%d,x=%d,y=%d", uid, x, y);
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