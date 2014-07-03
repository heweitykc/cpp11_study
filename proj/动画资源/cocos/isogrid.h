#ifndef __ISO_GRID_H__
#define __ISO_GRID_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class IsoGrid : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(IsoGrid);
	void setXAngle(float angle);
	void setYAngle(float angle);
	void setZAngle(float angle);
	void setCellSize(float size);
	void drawPoint(float x, float y, float z);
	void drawPoints(cocos2d::Vector<cocos2d::Vec3>* vecs);
	void drawCell(float x, float y, float z);
	void redraw();
	void sliderEvent1(Ref* pSender, cocos2d::ui::Slider::EventType type);
	void sliderEvent2(Ref* pSender, cocos2d::ui::Slider::EventType type);
private:
	float _xangle;
	float _yangle;
	float _zangle;
	float _cellSize;
	cocos2d::Vector<cocos2d::Vec3>* _vecs;

	cocos2d::DrawNode* _drawNode;
	cocos2d::ui::Slider* _slider1;
	cocos2d::ui::Slider* _slider2;
	cocos2d::LabelTTF* _label;
};

#endif