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

	return true;
}

void IsoGrid::moveItem(int roleIndex, int x, int y, int z)
{
	float startx = 100;
	float starty = 100;
	x = startx + x*_cellSize;
	z = starty + z*_cellSize;

	float sX = x * _cos_y_angle - z * _sin_y_angle;
	float z1 = z * _cos_y_angle + x * _sin_y_angle;
	float sY = y * _cos_x_angle - z1 * _sin_x_angle;
	_items[roleIndex]->setPosition(sX, sY);
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
	float startx = 100;
	float starty = 100;

	float sX = x * _cos_y_angle - z * _sin_y_angle;
	float z1 = z * _cos_y_angle + x * _sin_y_angle;
	float sY = y * _cos_x_angle - z1 * _sin_x_angle;
	//float z2 = z1 * cos(_xangle) + y * sin(_xangle);
	//log("x=%2f,y=%2f", sX, sY);
	_drawNode->drawDot(Vec2(sX, sY), 1, Color4F(1, 1, 1, 1));
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
	float startx = 100;
	float starty = 100;
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 18; j++){
			drawPoint(startx + i*_cellSize, 0, starty+j * _cellSize);
			drawPoint(startx + i * _cellSize, 0, starty + (j + 1) * _cellSize);
			drawPoint(startx + (i + 1) * _cellSize, 0, starty + j * _cellSize);
			drawPoint(startx + (i + 1) * _cellSize, 0, starty + (j + 1) * _cellSize);
		}
	}
	char str0[256] = {0};
	sprintf(str0, "xangle=%2f,yangle=%2f", _xangle, _yangle);
	_label->setString(str0);

	moveItem(0, 0, 0, 0);
	moveItem(1, 1, 0, 2);
	moveItem(2, 2, 0, 2);
	moveItem(3, 3, 0, 2);
	moveItem(4, 4, 0, 2);
	moveItem(5, 5, 0, 2);
}