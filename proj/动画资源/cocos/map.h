#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "role.h"
#include "cocostudio/CocoStudio.h"

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

	void addRole(RoleModel model, std::string dir);
	void updateRole(float x, float y);
	void removeRole();

private:
	cocostudio::Armature *hero;
	Role* _role;
	cocos2d::Vector<Node*> _rlist;
	cocos2d::Sprite* _bg;
	cocos2d::Sprite* _road;
	cocos2d::SpriteBatchNode *_actors;

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMove(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnd(cocos2d::Touch*, cocos2d::Event*);
	void logic(float dt);
};

#endif // __MAP_SCENE_H__