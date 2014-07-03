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
	_slider1->setPosition(Vec2(100, 100));
	addChild(_slider1);
	_slider1->addEventListener(CC_CALLBACK_2(IsoGrid::sliderEvent1, this));
	_slider1->setPercent(50);

	_slider2 = Slider::create();
	_slider2->loadBarTexture("ui/sliderTrack.png");
	_slider2->loadSlidBallTextures("ui/sliderThumb.png", "ui/sliderThumb.png", "");
	_slider2->loadProgressBarTexture("ui/sliderProgress.png");
	_slider2->setPosition(Vec2(100, 70));
	addChild(_slider2);
	_slider2->addEventListener(CC_CALLBACK_2(IsoGrid::sliderEvent2, this));
	_slider2->setPercent(50);

	_label = LabelTTF::create("Hello World", "Arial", 12);
	_label->setPosition(110, 200);
	addChild(_label);

	return true;
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
	float sX = x * cos(_yangle) - z * sin(_yangle);
	float z1 = z * cos(_yangle) + x * sin(_yangle);
	float sY = y * cos(_xangle) - z1 * sin(_xangle);
	float z2 = z1 * cos(_xangle) + y * sin(_xangle);
	log("x=%f,y=%f", sX, sY);
	_drawNode->drawDot(Vec2(sX, sY), 1, Color4F(1, 1, 1, 1));
}

void IsoGrid::drawCell(float x, float y, float z)
{
	float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
	
}

void IsoGrid::sliderEvent1(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED){
		int percent = _slider1->getPercent();		
		_xangle = (percent / 100.0f) * 3.1415926f - 3.1415926f / 2;
	}
	redraw();
}

void IsoGrid::sliderEvent2(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED){
		int percent = _slider2->getPercent();		
		_yangle = (percent / 100.0f) * 3.1415926f - 3.1415926f/2;
	}
	redraw();
}

void IsoGrid::drawPoints(Vector<cocos2d::Vec3>* vecs)
{
	_vecs = vecs;
}

void IsoGrid::redraw()
{
	/*
	for (size_t i = 0; i < _vecs->size(); i++)
	{
		drawPoint(_vecs->at(i).x, _vecs->at(i).y, _vecs->at(i).z);
	}
	*/
	_drawNode->clear();

	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 18; j++){
			log("%f  %f", _xangle, _yangle);
			drawPoint(i*20, 0, j*20);
			drawPoint(i * 20, 0, (j+1) * 20);
			drawPoint((i + 1) * 20, 0, j * 20);
			drawPoint((i + 1) * 20, 0, (j + 1) * 20);
			log("draw end");
		}
	}

	char str0[256] = {0};
	sprintf(str0, "xangle=%f,yangle=%f", _xangle, _yangle);
	_label->setString(str0);
}