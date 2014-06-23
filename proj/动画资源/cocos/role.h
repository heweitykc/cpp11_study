#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "pkgutil.h"

class Role : public cocos2d::Layer
{
public:
	enum State{ STOP, RUN};
	virtual bool init();	
	CREATE_FUNC(Role);
	void initModel(RoleModel model, std::string dir);
	void stop();
	void run();	
private:
	cocos2d::Sprite* _cc;
	cocos2d::Label* _titletxt;
	cocos2d::Animation* createAnimation(const char *fmt, int count, float fps);
	State state;
	RoleModel _model;
	std::string _dir;
};

#endif