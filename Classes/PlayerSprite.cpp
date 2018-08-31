#include "PlayerSprite.h"

USING_NS_CC;

#define SHOOTING_COOLDOWN 20

enum actList
{
	Wait,
	Move,
	Attack,
	Die,
	Victory,
	VictoryLoop
};

PlayerSprite::PlayerSprite()
{
	initValue();

	for (int i = 0; i < MAX_ANIM; i++)
	{
		anime[i].texture = SpriteFrameCache::getInstance();
		anime[i].name = getTypeName(i);
		anime[i].file = "GF/Noel/Noel-";
		anime[i].file.append(anime[i].name.c_str());
		anime[i].file.append(".plist");
		anime[i].texture->addSpriteFramesWithFile(anime[i].file);
		anime[i].maxFrame = getMaxFrame(i);
		anime[i].anchor = getAnchor(i);
	}
}

void PlayerSprite::initValue()
{
	addAnimInfo("wait",			40,	 Vec2(91, 25));
	addAnimInfo("move",			24,	 Vec2(82, 26));
	addAnimInfo("attack",		20,	 Vec2(101, 25));
	addAnimInfo("die",			51,	 Vec2(211, 70));
	addAnimInfo("victory",		140, Vec2(131, 34));
	addAnimInfo("victoryloop",	40,	 Vec2(94, 25));

	ShootingCooldown = SHOOTING_COOLDOWN;
	isShootingCooldown = false;
}

void PlayerSprite::addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor)
{
	m_name.push_back(_name);
	m_maxFrame.push_back(_maxFrame);
	m_anchor.push_back(_anchor);
}

std::string PlayerSprite::getTypeName(int _type)
{
	return m_name[_type];
}

int PlayerSprite::getMaxFrame(int _type)
{
	return m_maxFrame[_type];
}

Vec2 PlayerSprite::getAnchor(int _type)
{
	return m_anchor[_type];
}

void PlayerSprite::setAnimation(cocos2d::Sprite* _sprite, int _type)
{
	_sprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;

	for (int i = 0; i < anime[_type].maxFrame; i++)
	{
		char fileName[30];
		sprintf(fileName, "BB_Noel-%s-%03d.png", anime[_type].name.c_str(), i);
		SpriteFrame* frame = anime[_type].texture->getSpriteFrameByName(fileName);
		animFrames.pushBack(frame);
	}

	char fileName[30];
	sprintf(fileName, "BB_Noel-%s-000.png", anime[_type].name.c_str());
	bool saveFlip = _sprite->isFlippedX();
	_sprite->initWithSpriteFrameName(fileName);
	_sprite->setFlippedX(saveFlip);

	float wW = _sprite->getContentSize().width;
	float wH = _sprite->getContentSize().height;

	float aX = anime[_type].anchor.x / wW;
	float aY = anime[_type].anchor.y / wH;
	float faX = (wW - anime[_type].anchor.x) / wW;

	if (!_sprite->isFlippedX())
		_sprite->setAnchorPoint(Vec2(aX, aY));
	else
		_sprite->setAnchorPoint(Vec2(faX, aY));

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.025f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
		
	if (_type == actList::Wait || _type == actList::Move || _type == actList::VictoryLoop)
		_sprite->runAction(rep);
	else if (_type == actList::Attack)
	{
		ShootingCooldown = true;
		auto seq = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(PlayerSprite::setShootingCooldown, this)),
			animate, 
			CallFunc::create(CC_CALLBACK_0(PlayerSprite::setAnimation, this, _sprite, actList::Wait)),
			nullptr);
		_sprite->runAction(seq);
	}
	else if (_type == actList::Victory)
	{
		auto seq = Sequence::create(
			animate,
			CallFunc::create(CC_CALLBACK_0(PlayerSprite::setAnimation, this, _sprite, actList::VictoryLoop)),
			nullptr);
		_sprite->runAction(seq);
	}
	else if (_type == Die)
	{
		_sprite->runAction(animate);
	}
}

//==========================================================

void PlayerSprite::setShootingCooldown()
{
	ShootingCooldown = SHOOTING_COOLDOWN;
	isShootingCooldown = true;
}

void PlayerSprite::runShootingCooldown()
{
	if (ShootingCooldown <= 0)
		isShootingCooldown = false;
	else
		ShootingCooldown--;
}

bool PlayerSprite::isShooting()
{
	return isShootingCooldown;
}

int PlayerSprite::getShootingCooldown()
{
	return ShootingCooldown;
}
