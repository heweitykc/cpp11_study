#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"

class Role : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Role);
	void setFace(float degreeX, float degreeZ);
	void run();
	void stop();
private:
	cocos2d::Sprite3D* _role3d;
};

#endif