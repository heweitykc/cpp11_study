#include "role.h"

USING_NS_CC;

bool Role::init()
{	
	
	auto normal = createAnimation("attack (%d).png", 9, 12);
	normal->setRestoreOriginalFrame(true);
	auto animN = Animate::create(normal);

	_cc = Sprite::create();
	_cc->runAction(RepeatForever::create(animN));
	addChild(_cc);

	return true;
}

Animation* Role::createAnimation(const char *fmt, int count, float fps)
{
	auto frameCache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> animFrames(count);
	char str[100] = { 0 };
	for (int i = 1; i <= count; i++){
		sprintf(str, fmt, i);
		auto frame = frameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	return  Animation::createWithSpriteFrames(animFrames, 1 / fps);
}