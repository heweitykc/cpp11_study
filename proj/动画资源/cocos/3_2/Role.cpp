#include "Role.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"

USING_NS_CC;

bool Role::init()
{
	_role3d = Sprite3D::create("Sprite3DTest/girl.c3t");
	addChild(_role3d);
	_role3d->setScale(0.2);
	_role3d->setPosition(0, 10);
	setFace(-60.0f, 0.0f);
	return true;
}

void Role::run()
{
	auto animation = Animation3D::getOrCreate("Sprite3DTest/girl.c3t");
	auto animate = Animate3D::create(animation);
	animate->setSpeed(3);
	_role3d->runAction(RepeatForever::create(animate));
}

void Role::stop()
{
	_role3d->stopAllActions();
}

void Role::setFace(float degreeX, float degreeZ)
{
	_role3d->setRotation3D(Vec3(degreeX, 0.0f, degreeZ));
}