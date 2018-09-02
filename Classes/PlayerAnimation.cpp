#include "PlayerAnimation.h"
#include "GlobalDef.h"

USING_NS_CC;

#define SHOOTING_COOLDOWN 20

PlayerAnimation::PlayerAnimation()
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

void PlayerAnimation::initValue()
{
	addAnimInfo("wait",			40,	 Vec2(91, 25));
	addAnimInfo("move",			24,	 Vec2(82, 26));
	addAnimInfo("attack",		20,	 Vec2(101, 25));
	addAnimInfo("die",			51,	 Vec2(211, 70));
	addAnimInfo("victory",		140, Vec2(131, 34));
	addAnimInfo("victoryloop",	40,	 Vec2(94, 25));

	ShootingCooldown = 0;
	isShootingCooldown = false;
}

void PlayerAnimation::addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor)
{
	m_name.push_back(_name);
	m_maxFrame.push_back(_maxFrame);
	m_anchor.push_back(_anchor);
}

std::string PlayerAnimation::getTypeName(int _type)
{
	return m_name[_type];
}

int PlayerAnimation::getMaxFrame(int _type)
{
	return m_maxFrame[_type];
}

Vec2 PlayerAnimation::getAnchor(int _type)
{
	return m_anchor[_type];
}

void PlayerAnimation::setAnimation(int _type)
{
	this->stopAllActions();

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
	bool saveFlip = this->isFlippedX();
	this->initWithSpriteFrameName(fileName);
	this->setFlippedX(saveFlip);

	float wW = this->getContentSize().width;
	float wH = this->getContentSize().height;

	float aX = anime[_type].anchor.x / wW;
	float aY = anime[_type].anchor.y / wH;
	float faX = (wW - anime[_type].anchor.x) / wW;

	if (!this->isFlippedX())
		this->setAnchorPoint(Vec2(aX, aY));
	else
		this->setAnchorPoint(Vec2(faX, aY));

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.025f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
		
	if (_type == actList::Wait || _type == actList::Move || _type == actList::VictoryLoop)
		this->runAction(rep);
	else if (_type == actList::Attack)
	{
		ShootingCooldown = true;
		
		auto seq = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setShootingCooldown, this)),
			animate, 
			CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setAnimation, this, actList::Wait)),
			nullptr);
		this->runAction(seq);
	}
	else if (_type == actList::Victory)
	{
		auto seq = Sequence::create(
			animate,
			CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setAnimation, this, actList::VictoryLoop)),
			nullptr);
		this->runAction(seq);
	}
	else if (_type == Die)
	{
		this->runAction(animate);
	}
}

//==========================================================

void PlayerAnimation::setShootingCooldown()
{
	ShootingCooldown = 0;
	isShootingCooldown = true;
}

void PlayerAnimation::runShootingCooldown()
{
	if (ShootingCooldown >= SHOOTING_COOLDOWN)
		isShootingCooldown = false;
	else
		ShootingCooldown++;
}

bool PlayerAnimation::isShooting()
{
	return isShootingCooldown;
}

int PlayerAnimation::getShootingCooldown()
{
	return ShootingCooldown;
}
