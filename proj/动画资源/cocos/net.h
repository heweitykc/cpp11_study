#ifndef __NET_H__
#define __NET_H__

#include "cocos2d.h"
#include "network\WebSocket.h"
#include <string>

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
	void send(std::string& msg, int cmd);
	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
private:
	network::WebSocket _wsi;
	int _uid;
};

#endif