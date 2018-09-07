#include "PlayerAnimation.h"
#include "GlobalDef.h"

USING_NS_CC;

#define SHOOTING_COOLDOWN 13
#define MG_A_DELAY 64
#define MG_C_DELAY 37
#define MG_INTERVAL 6

bool PlayerAnimation::init()
{
	if (!Sprite::init()) return false;

	//============================================================

	initValue();

	for (int i = 0; i < MAX_ANIM; i++)
	{
		anime[i].texture = SpriteFrameCache::getInstance();
		anime[i].name = getTypeName(i);
		anime[i].file = "GF/Noel/Noel-";
		anime[i].file.append(anime[i].name.getCString());
		anime[i].file.append(".plist");
		anime[i].texture->addSpriteFramesWithFile(anime[i].file.getCString());
		anime[i].maxFrame = getMaxFrame(i);
		anime[i].anchor = getAnchor(i);
	}

	//============================================================

	return true;
}

void PlayerAnimation::initValue()
{
	addAnimInfo("wait",			40,	 Vec2(91, 25));
	addAnimInfo("move",			24,	 Vec2(82, 26));
	addAnimInfo("attack",		20,	 Vec2(101, 25));
	addAnimInfo("die",			51,	 Vec2(211, 70));
	addAnimInfo("victory",		140, Vec2(131, 34));
	addAnimInfo("victoryloop",	40,	 Vec2(94, 25));
	addAnimInfo("shotA",		13,	 Vec2(101, 25));
	addAnimInfo("mgA",			37,  Vec2(221, 29));
	addAnimInfo("mgB",			13,  Vec2(221, 29));
	addAnimInfo("mgC",			25,  Vec2(221, 29));

	ShootingCooldown = 0;
	isShootingCooldown = false;

	MGStartDelay = 0;
	MGEndDelay = 0;
	isMGRun = false;
	isMGShooting = false;
	MGPhase = false;
	MGInterval = MG_INTERVAL;
	MGIntervaln = 0;

	saveType = -1;
}

void PlayerAnimation::setAnimation(int _type)
{
	if (saveType != _type)
	{
		saveType = _type;

		this->stopAllActions();

		Vector<SpriteFrame*> animFrames;

		for (int i = 0; i < anime[_type].maxFrame; i++)
		{
			char fileName[30];
			sprintf(fileName, "BB_Noel-%s-%03d.png", anime[_type].name.getCString(), i);
			SpriteFrame* frame = anime[_type].texture->getSpriteFrameByName(fileName);
			animFrames.pushBack(frame);
		}

		char fileName[30];
		sprintf(fileName, "BB_Noel-%s-000.png", anime[_type].name.getCString());
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

		if (_type == actList::Wait || _type == actList::Move || _type == actList::VictoryLoop || _type == actList::mgB)
			this->runAction(rep);
		else if (_type == actList::Attack || _type == actList::shotA)
		{
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
		else if (_type == actList::mgA)
		{
			auto seq = Sequence::create(
				CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setMGStartDelay, this)),
				animate,
				nullptr);
			this->runAction(seq);
		}
		else if (_type == actList::mgC)
		{
			auto seq = Sequence::create(
				CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setMGEndDelay, this)),
				animate,
				CallFunc::create(CC_CALLBACK_0(PlayerAnimation::setAnimation, this, actList::Wait)),
				nullptr);
			this->runAction(seq);
		}
	}
}

//==========================================================

void PlayerAnimation::runShootingCooldown()
{
	if (ShootingCooldown >= SHOOTING_COOLDOWN)
		isShootingCooldown = false;
	else
		ShootingCooldown++;
}

//==========================================================

void PlayerAnimation::runMGStartDelay()
{
	if (MGStartDelay >= MG_A_DELAY)
	{
		isMGShooting = true;
		MGPhase = true;
		MGStartDelay = 0;
	}
	else
		MGStartDelay++;
}

void PlayerAnimation::runMGEndDelay()
{
	MGIntervaln = 0;
	if (MGEndDelay >= MG_C_DELAY)
	{
		isMGRun = false;
		MGPhase = false;
		MGEndDelay = 0;
	}
	else
		MGEndDelay++;
}

void PlayerAnimation::runMGInterval()
{
	if (MGIntervaln < MGInterval)
		MGIntervaln++;
	else
		MGIntervaln = 0;
}
