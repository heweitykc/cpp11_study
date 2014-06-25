#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    _bg = Sprite::create("map0.jpg");
	_bg->setScale(2);
	_bg->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(_bg);
    
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	_role = Role::create();
	_bg->addChild(_role);

	auto role2 = Role::create();
	_bg->addChild(role2);
	role2->setPosition(40, 50);
	role2->run();

	auto role3 = Role::create();
	_bg->addChild(role3);
	role3->setPosition(10, 10);
	role3->run();

	auto role4 = Role::create();
	_bg->addChild(role4);
	role4->setPosition(20, 20);
	role4->run();

	auto role5 = Role::create();
	_bg->addChild(role5);
	role5->setPosition(30, 30);
	role5->run();

	auto bg2 = Sprite::create("map1.png");
	bg2->setPosition(400, 200);
	this->addChild(bg2);

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 v2 = touch->getLocation();
	v2 = _bg->convertToNodeSpace(v2);
	Vec2 v1 = _role->getPosition();

	float len = v2.distance(v1);
	float per = 1.0f / 100.0f;

	auto action1 = CallFunc::create(
		[&](){
		_role->stop();
	});

	_role->run();
	_role->stopAllActions();
	_role->runAction(Sequence::create(MoveTo::create(per*len, v2), action1, NULL));
	if (v2.x > v1.x){
		_role->setFace(-60.0f, 0.0f);
	} else {
		_role->setFace(60.0f, 180.0f);
	}
	return false;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
