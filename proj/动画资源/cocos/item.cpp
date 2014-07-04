#include "item.h"

USING_NS_CC;

bool GridItem::init()
{	
	_drawNode = DrawNode::create();
	_drawNode->drawDot(Vec2(0,0), 4, Color4F(1, 1, 0, 1));
	addChild(_drawNode);
	return true;
}
