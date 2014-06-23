#ifndef __NET_H__
#define __NET_H__

#include <string>
#include "cocos2d.h"
#include "network\WebSocket.h"
#include "pkgutil.h"

USING_NS_CC;

class NetLayer : public network::WebSocket::Delegate
{
public:
	static NetLayer* getInstance();
	NetLayer();
	~NetLayer();
	void init();
	void connect();
	void close();
	void send(netpack& pack);

	void clientLogin();
	void clientMove(int x,int y);

	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

	EventDispatcher dispatcher;

private:
	network::WebSocket _wsi;
	int _uid;	
};

#endif