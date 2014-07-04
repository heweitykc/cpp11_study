#include "item.h"

USING_NS_CC;

bool GridItem::init()
{	
	_drawNode = DrawNode::create();
	addChild(_drawNode);
	return true;
}

void GridItem::update(int size)
{
	_drawNode->clear();
	_drawNode->drawDot(Vec2(0, 0), size, Color4F(1, 1, 0, 1));
}
