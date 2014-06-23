#include "role.h"

USING_NS_CC;

bool Role::init()
{	
	_cc = Sprite::create();
	_cc->setPositionY(210);
	addChild(_cc);

	_titletxt = Label::create();
	addChild(_titletxt);
	
	return true;
}

void Role::initModel(RoleModel model, std::string dir)
{
	_dir = dir;
	_model = model;
	setPosition(Vec2(_model.x,_model.y));
	stop();

	char titlestr[256] = {0};
	std::sprintf(titlestr, "player%d", _model.uid);
	_titletxt->setString(titlestr);
}

void Role::stop()
{
	if (state == Role::State::STOP) return;
	state = Role::State::STOP;
	_cc->stopAllActions();
	auto normal = createAnimation("stand (%d).png", 6, 12);
	normal->setRestoreOriginalFrame(true);
	auto animN = Animate::create(normal);
	_cc->runAction(RepeatForever::create(animN));
}

void Role::run()
{
	if (state == Role::State::RUN) return;
	state = Role::State::RUN;
	_cc->stopAllActions();
	auto normal = createAnimation("move (%d).png", 6, 12);
	normal->setRestoreOriginalFrame(true);
	auto animN = Animate::create(normal);
	_cc->runAction(RepeatForever::create(animN));
}

Animation* Role::createAnimation(const char *fmt, int count, float fps)
{
	auto frameCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(count);
	char str[100] = { 0 };
	for (int i = 1; i <= count; i++){
		sprintf(str, fmt, i);
		auto frame = frameCache->getSpriteFrameByName(_dir+str);
		animFrames.pushBack(frame);
	}
	return  Animation::createWithSpriteFrames(animFrames, 1 / fps);
}