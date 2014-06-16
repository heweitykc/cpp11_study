#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"

class Role : public cocos2d::Sprite
{
public:
	virtual bool init();	
	CREATE_FUNC(Role);
private:
	cocos2d::Animation* createAnimation(const char *fmt, int count, float fps);
};

#endif