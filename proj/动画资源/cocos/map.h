#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "role.h"

class GameMap : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameMap);

private:
	Role* _role;
	cocos2d::Sprite* _bg;
	cocos2d::Sprite* _road;
	cocos2d::SpriteBatchNode *_actors;

	void logic(float dt);
};

#endif // __MAP_SCENE_H__