#include "isogrid.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

bool IsoGrid::init()
{	
	auto s = Director::getInstance()->getWinSize();
	_drawNode = DrawNode::create();
	addChild(_drawNode, 10);

	_xangle = 0;
	_yangle = 0;
	_zangle = 0;
	_cellSize = 10;

	_slider1 = Slider::create();
	_slider1->loadBarTexture("ui/sliderTrack.png");
	_slider1->loadSlidBallTextures("ui/sliderThumb.png", "ui/sliderThumb.png", "");
	_slider1->loadProgressBarTexture("ui/sliderProgress.png");
	_slider1->setPosition(Vec2(70, 300));
	addChild(_slider1);
	_slider1->addEventListener(CC_CALLBACK_2(IsoGrid::sliderEvent1, this));
	_slider1->setPercent(50);

	_slider2 = Slider::create();
	_slider2->loadBarTexture("ui/sliderTrack.png");
	_slider2->loadSlidBallTextures("ui/sliderThumb.png", "ui/sliderThumb.png", "");
	_slider2->loadProgressBarTexture("ui/sliderProgress.png");
	_slider2->setPosition(Vec2(70, 280));
	addChild(_slider2);
	_slider2->addEventListener(CC_CALLBACK_2(IsoGrid::sliderEvent2, this));
	_slider2->setPercent(50);

	_slider3 = Slider::create();
	_slider3->loadBarTexture("ui/sliderTrack.png");
	_slider3->loadSlidBallTextures("ui/sliderThumb.png", "ui/sliderThumb.png", "");
	_slider3->loadProgressBarTexture("ui/sliderProgress.png");
	_slider3->setPosition(Vec2(70, 260));
	addChild(_slider3);
	_slider3->addEventListener(CC_CALLBACK_2(IsoGrid::sliderEvent3, this));
	_slider3->setPercent(50);

	_label = LabelTTF::create("Hello World", "Arial", 8);
	_label->setPosition(100, 310);
	addChild(_label);

	_items[0] = GridItem::create();
	addChild(_items[0]);
	_items[1] = GridItem::create();
	addChild(_items[1]);
	_items[2] = GridItem::create();
	addChild(_items[2]);
	_items[3] = GridItem::create();
	addChild(_items[3]);
	_items[4] = GridItem::create();
	addChild(_items[4]);
	_items[5] = GridItem::create();
	addChild(_items[5]);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(IsoGrid::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}

bool IsoGrid::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 v2 = touch->getLocation();
	v2 = this->convertToNodeSpace(v2);
	char str0[256] = { 0 };
	Vec3 isop;
	screen2iso(isop, Vec3(v2.x, v2.y, 0));
	sprintf(str0, "x=%f,z=%f", round(isop.x), round(isop.z));
	_label->setString(str0);

	moveItem(0, isop.x, v2.y, isop.z);

	return false;
}

void IsoGrid::moveItem(int roleIndex, int x, int y, int z)
{
	_items[roleIndex]->gridPos.x = x;
	_items[roleIndex]->gridPos.y = y;
	_items[roleIndex]->gridPos.z = z;

	Vec3 v2;
	iso2screen(Vec3(x, y, z), v2);
	_items[roleIndex]->setPosition(Vec2(v2.x, v2.y));
	_items[roleIndex]->update(_cellSize/2);
}

void IsoGrid::setXAngle(float xangle)
{
	_xangle = xangle;
}

void IsoGrid::setYAngle(float yangle)
{
	_yangle = yangle;
}

void IsoGrid::setZAngle(float zangle)
{
	_zangle = zangle;
}

void IsoGrid::setCellSize(float size)
{
	_cellSize = size;
}

void IsoGrid::drawPoint(float x, float y, float z)
{
	Vec3 v2;
	iso2screen(Vec3(x, y, z), v2);
	_drawNode->drawDot(Vec2(v2.x,v2.y), 1, Color4F(1, 1, 1, 1));
}

void IsoGrid::sliderEvent1(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED){
		int percent = _slider1->getPercent();
		_xangle = (percent / 100.0f) * 3.1415926f - 3.1415926f / 2;
	}
	this->unschedule(schedule_selector(IsoGrid::redraw));
	this->scheduleOnce(schedule_selector(IsoGrid::redraw), 0.01);
}

void IsoGrid::sliderEvent2(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED){
		int percent = _slider2->getPercent();		
		_yangle = (percent / 100.0f) * 3.1415926f - 3.1415926f/2;
	}
	this->unschedule(schedule_selector(IsoGrid::redraw));
	this->scheduleOnce(schedule_selector(IsoGrid::redraw), 0.05);
}

void IsoGrid::sliderEvent3(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED){
		int percent = _slider3->getPercent();
		_cellSize = percent*0.5;
	}
	this->unschedule(schedule_selector(IsoGrid::redraw));
	this->scheduleOnce(schedule_selector(IsoGrid::redraw), 0.05);
}

void IsoGrid::drawPoints(Vector<cocos2d::Vec3>* vecs)
{
	_vecs = vecs;
}

void IsoGrid::redraw(float dt)
{
	_sin_x_angle = sin(_xangle);
	_cos_x_angle = cos(_xangle);
	_sin_y_angle = sin(_yangle);
	_cos_y_angle = cos(_yangle);

	_drawNode->clear();
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 18; j++){
			drawPoint(i, 0, j);
		}
	}
	char str0[256] = {0};
	sprintf(str0, "xangle=%2f,yangle=%2f", _xangle, _yangle);
	_label->setString(str0);

	moveItem(0, 0, 0, 0);
	moveItem(1, 1, 0, 12);
	moveItem(2, 2, 0, 12);
	moveItem(3, 3, 0, 15);
	moveItem(4, 4, 0, 12);
	moveItem(5, 16, 0, 17);
}

void IsoGrid::iso2screen(Vec3& isoP, Vec3& screenP)
{
	isoP.y = 0;
	screenP.x = isoP.x * _cos_y_angle - isoP.z * _sin_y_angle;

	float z1 = isoP.z * _cos_y_angle + isoP.x * _sin_y_angle;
	screenP.y = isoP.y * _cos_x_angle - z1 * _sin_x_angle;

	screenP.x *= _cellSize;
	screenP.y *= _cellSize;
}

void IsoGrid::screen2iso(Vec3& isoP, Vec3& screenP)
{	
	screenP.x /= _cellSize;
	screenP.y /= _cellSize;

	isoP.y = 0;
	float z1 = -1 * screenP.y / _sin_x_angle;

	isoP.x = (z1 * _sin_y_angle + screenP.x * _cos_y_angle) / (_cos_y_angle* _cos_y_angle + _sin_y_angle * _sin_y_angle);
	isoP.z = (z1 - isoP.x * _sin_y_angle) / _cos_y_angle;

	isoP.x = round(isoP.x);
	isoP.z = round(isoP.z);
}