#include "map.h"
#include "net.h"

USING_NS_CC;
using namespace cocostudio;

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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("magician/magician.plist", "magician/magician.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldiers/soldiers.plist","soldiers/soldiers.png");

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

	this->schedule(schedule_selector(GameMap::logic),0);
	
	RoleModel model;
	model.uid = 100;
	model.name = "hello";
	model.position.set(100,100);
	addRole(model,"magician");
	
	RoleModel model1;
	model1.uid = 101;
	model1.name = "hel2lo";
	model1.position.set(200, 120);
	addRole(model1, "soldiers");
	
	_role = dynamic_cast<Role*>(_rlist.at(1));

	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
		"tauren/tauren0.png", "tauren/tauren0.plist", "tauren/tauren.ExportJson");
	hero = Armature::create("tauren");
	hero->getAnimation()->play("loading");
	hero->setScale(0.5f);
	hero->setPosition(200,300);
	_road->addChild(hero);
	_rlist.pushBack(hero);

	NetLayer::getInstance()->connect();

	return true;
}

void GameMap::addRole(RoleModel model, std::string dir)
{
	auto role = Role::create();
	role->initModel(model, dir);
	_road->addChild(role);

	_rlist.pushBack(role);
}

void GameMap::updateRole(float x, float y)
{

}

void GameMap::removeRole()
{

}

bool GameMap::onTouchBegan(Touch* touch, Event* event)
{
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
	if (v2.x > v1.x){
		_role->setScaleX(1);
		hero->getAnimation()->play("loading");
	} else {
		_role->setScaleX(-1);
		hero->getAnimation()->play("attack");
	}
		
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
	std::sort(_rlist.begin(), _rlist.end(), [this](Node* a, Node* b){
		return b->getPositionY() < a->getPositionY();
	});
	int len = _rlist.size();
	for (int i = 0; i < len; i++){
		_road->reorderChild(_rlist.at(i), i);
	}
	
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
