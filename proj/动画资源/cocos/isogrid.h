#ifndef __ISO_GRID_H__
#define __ISO_GRID_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "roadsearch.h"
#include "item.h"

class IsoGrid : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(IsoGrid);
	void setXAngle(float angle);
	void setYAngle(float angle);
	void setZAngle(float angle);
	void setCellSize(float size);
	inline void drawPoint(float x, float y, float z);
	void drawPoints(cocos2d::Vector<cocos2d::Vec3>* vecs);	
	void redraw(float dt);
	void sliderEvent1(Ref* pSender, cocos2d::ui::Slider::EventType type);
	void sliderEvent2(Ref* pSender, cocos2d::ui::Slider::EventType type);
	void sliderEvent3(Ref* pSender, cocos2d::ui::Slider::EventType type);
	void moveItem(int roleIndex, int x, int y, int z);
private:
	float _xangle;
	float _yangle;
	float _zangle;
	float _cellSize;
	float _sin_x_angle;
	float _cos_x_angle;
	float _sin_y_angle;
	float _cos_y_angle;
	cocos2d::Vector<cocos2d::Vec3>* _vecs;
	RoadSearch _search;

	cocos2d::DrawNode* _drawNode;
	cocos2d::ui::Slider* _slider1;
	cocos2d::ui::Slider* _slider2;
	cocos2d::ui::Slider* _slider3;
	cocos2d::LabelTTF* _label;
	GridItem* _items[6];

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void iso2screen(cocos2d::Vec3& isoP, cocos2d::Vec3& screenP);
	void screen2iso(cocos2d::Vec3& isoP, cocos2d::Vec3& screenP);
};

#endif