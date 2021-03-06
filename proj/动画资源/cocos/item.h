#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

class GridItem : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GridItem);	
	cocos2d::Vec3 gridPos;
	void update(int size);
private:
	cocos2d::DrawNode* _drawNode;
};

#endif
