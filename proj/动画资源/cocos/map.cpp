#include "map.h"
#include "net.h"

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

	_bg = Sprite::create("1.jpg");
	this->addChild(_bg);
	_road = Sprite::create("1.png");
	this->addChild(_road);

	auto bgsize = _bg->getContentSize();
	auto size = _road->getContentSize();
	_bg->setPosition(bgsize.width / 2, bgsize.height / 2 + (size.height-bgsize.height));
	_road->setPosition(size.width / 2,  size.height / 2);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = CC_CALLBACK_2(GameMap::onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(GameMap::onTouchMove, this);
	listener1->onTouchEnded = CC_CALLBACK_2(GameMap::onTouchEnd, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _road);

	this->schedule(schedule_selector(GameMap::logic));

	//NetLayer::getInstance()->connect();

	RoleModel model;
	model.id = 100;
	model.name = "hello";
	model.position.set(100,100);
	addRole(model);
	setCurrent(model.id);
	
	RoleModel model1;
	model1.id = 101;
	model1.name = "hel2lo";
	model1.position.set(200, 100);
	addRole(model1);
	//setCurrent(model1.id);

	return true;
}

void GameMap::addRole(RoleModel model)
{
	auto role = Role::create();
	role->initModel(model);		
	_road->addChild(role);

	_rlist.insert(model.id, role);
}

void GameMap::updateRole(float x, float y)
{

}

void GameMap::removeRole()
{

}

void GameMap::setCurrent(int id)
{
	_role = _rlist.at(id);
}

bool GameMap::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	Vec2 v2 = touch->getLocation();
	v2 = _road->convertToNodeSpace(v2);
	Vec2 v1 = _role->getPosition();
	float len = v2.distance(v1);
	float per = 1.0f / 200.0f;
	_role->run();

	auto action1 = CallFunc::create(
		[&](){
		_role->stop();
	});
	_role->stopAllActions();
	_role->runAction(Sequence::create(MoveTo::create(per*len, v2), action1, NULL));
	if (v2.x > v1.x)
		_role->setScaleX(1);
	else
		_role->setScaleX(-1);
	return true;
}

void GameMap::onTouchMove(cocos2d::Touch*, cocos2d::Event*)
{

}
void GameMap::onTouchEnd(cocos2d::Touch*, cocos2d::Event*)
{

}

void GameMap::logic(float dt)
{
	//_bg->setPositionX(_bg->getPositionX()+1);
	//保证玩家在视野内
	auto vsize = Director::getInstance()->getVisibleSize();
	auto size = _road->getContentSize();
	float tx = _role->getPositionX()*-1.0f + size.width / 2.0f + vsize.width / 2.0f;
	if (tx > size.width / 2.0f) return;
	if (tx < (size.width / -2.0f + vsize.width)) return;
	float diff = tx - _road->getPositionX();
	_road->setPositionX(tx);

	auto bgsize = _bg->getContentSize();
	diff = diff * (bgsize.width - vsize.width) / (size.width - vsize.width);
	_bg->setPositionX(diff + _bg->getPositionX());
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
