#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"

class Role : public cocos2d::Layer
{
public:
	enum State{ STOP, RUN};
	virtual bool init();	
	CREATE_FUNC(Role);
	void stop();
	void run();	
private:
	cocos2d::Sprite* _cc;
	cocos2d::Animation* createAnimation(const char *fmt, int count, float fps);
	State state;
};

#endif