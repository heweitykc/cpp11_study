#include "role.h"

USING_NS_CC;

bool Role::init()
{	
	Animation *animation = createAnimation("stand (%d).png", 8, 12);
	Action* act = RepeatForever::create(Animate::create(animation));
	this->runAction(act);

	return true;
}

Animation* Role::createAnimation(const char *fmt, int count, float fps)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> frames;

	int i;
	for (i = 1; i <= count; i++) {
		const char *png = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		frames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(frames, 1 / fps);
}