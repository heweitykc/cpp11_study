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

	_bg = Sprite::create("1.jpg");
	this->addChild(_bg);
	_road = Sprite::create("1.png");
	this->addChild(_road);

	auto bgsize = _bg->getContentSize();
	auto size = _road->getContentSize();
	_bg->setPosition(bgsize.width / 2, bgsize.height / 2 + (size.height-bgsize.height));
	_road->setPosition(size.width / 2, size.height / 2);	

	_role = Role::create();
	_role->setPosition(0, 210);
	_road->addChild(_role);
	_role->stop();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [this](Touch* touch, Event* event){
		log("onTouchBegan");
		Vec2 v2 = touch->getLocation();
		v2 = _road->convertToNodeSpace(v2);
		v2.y += 100;
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
	};

	listener1->onTouchMoved = [this](Touch* touch, Event* event){
		log("onTouchMoved");
	};

	listener1->onTouchEnded = [this](Touch* touch, Event* event){
		log("onTouchEnded");
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _road);

	this->schedule(schedule_selector(GameMap::logic));

	return true;
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
