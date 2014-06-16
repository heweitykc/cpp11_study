#include "map.h"

USING_NS_CC;


Scene* GameMap::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	GameMap *layer = GameMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMap::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("magician.plist");
	_actors = SpriteBatchNode::create("magician.png");
	this->addChild(_actors);

	_role = Role::create();
	_actors->addChild(_role);

	return true;
}

void GameMap::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
