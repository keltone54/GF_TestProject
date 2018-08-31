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
	m_name.push_back("wait");
	m_name.push_back("move");
	m_name.push_back("attack");
	m_name.push_back("die");
	m_name.push_back("victory");
	m_name.push_back("victoryloop");

	m_maxFrame.push_back(40);
	m_maxFrame.push_back(24);
	m_maxFrame.push_back(20);
	m_maxFrame.push_back(51);
	m_maxFrame.push_back(140);
	m_maxFrame.push_back(40);

	m_anchor.push_back(Vec2(91, 25));
	m_anchor.push_back(Vec2(82, 26));
	m_anchor.push_back(Vec2(101, 25));
	m_anchor.push_back(Vec2(211, 70));
	m_anchor.push_back(Vec2(131, 34));
	m_anchor.push_back(Vec2(94, 25));

	ShootingCooldown = SHOOTING_COOLDOWN;
	isShootingCooldown = false;
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


// SHOOTING COOLDOWN

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
