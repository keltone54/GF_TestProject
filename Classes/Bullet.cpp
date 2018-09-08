#include "Bullet.h"

bool Bullet::init()
{
	if (!Sprite::init()) return false;
	//============================================================
	// 초기화
	initValue();
	//============================================================
	// 내용



	//============================================================
	return true;
}

void Bullet::initValue()
{
	bulletType = 0;
	maxRange = 960;
	speed = 1.0f;

	Fire_txCache = Director::getInstance()->getTextureCache()->addImage("GF/Effect/shotfire.png");
}

void Bullet::BulletCreate()
{
	if(bulletType == 0)
		txCache = Director::getInstance()->getTextureCache()->addImage("GF/Bullet/bullet_HG.png");
	else if (bulletType == 1)
		txCache = Director::getInstance()->getTextureCache()->addImage("GF/Bullet/bullet_RF.png");
	else if (bulletType == 2)
		txCache = Director::getInstance()->getTextureCache()->addImage("GF/Bullet/bullet_MG.png");
	else
		txCache = Director::getInstance()->getTextureCache()->addImage("GF/Bullet/bullet_HG.png");

	auto blt = Sprite::createWithTexture(txCache);
	this->addChild(blt);

	if (this->isFlippedX())
	{
		maxRange = -maxRange;
		blt->setFlippedX(true);
	}

	auto seq = Sequence::create(
		MoveBy::create(speed, Vec2(maxRange, -40 + random(0, 80))),
		Hide::create(), nullptr);

	setBulletBoundBox(blt->getBoundingBox());

	this->runAction(seq);
}

void Bullet::setBulletBoundBox(Rect _rect)
{
	boundBox = _rect;
}

Rect Bullet::getBulletBoundBox()
{
	return boundBox;
}