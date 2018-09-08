#include "EnemyAnimation.h"
#include "GlobalDef.h"

bool EnemyAnimation::init(int _enemyType)
{
	if (!Sprite::init()) return false;

	//============================================================
	initValue(_enemyType);
	enemyType = _enemyType;

	for (int i = 0; i < MAX_ANIM; i++)
	{
		anime[i].texture = SpriteFrameCache::getInstance();
		anime[i].name = getTypeName(i);
		anime[i].file = "GF/Enemy/";
		anime[i].file.append(enemyName.getCString());
		anime[i].file.append("/");
		anime[i].file.append(enemyName.getCString());
		anime[i].file.append("-");
		anime[i].file.append(anime[i].name.getCString());
		anime[i].file.append(".plist");
		anime[i].texture->addSpriteFramesWithFile(anime[i].file.getCString());
		anime[i].maxFrame = getMaxFrame(i);
		anime[i].anchor = getAnchor(i);
	}

	//============================================================

	return true;
}

void EnemyAnimation::initValue(int _enemyType)
{
	switch (_enemyType)
	{
	case enemyType::Aegis:
		enemyName = "Aegis";

		addAnimInfo("wait",   54, Vec2(86,  24));
		addAnimInfo("move",	  54, Vec2(78,  24));
		addAnimInfo("attack", 44, Vec2(94,  24));
		addAnimInfo("die1",	  80, Vec2(75,  51));
		addAnimInfo("die2",	  70, Vec2(104, 50));
		addAnimInfo("die3",	  47, Vec2(221, 37));
		break;
	}

	saveType = -1;
}

void EnemyAnimation::setAnimation(int _type)
{
	if (saveType != _type)
	{
		saveType = _type;

		this->stopAllActions();

		Vector<SpriteFrame*> animFrames;

		for (int i = 0; i < anime[_type].maxFrame; i++)
		{
			char fileName[40];
			sprintf(fileName, "%s-%s-%03d.png", enemyName.getCString(), anime[_type].name.getCString(), i);
			SpriteFrame* frame = anime[_type].texture->getSpriteFrameByName(fileName);
			animFrames.pushBack(frame);
		}

		char fileName[40];
		sprintf(fileName, "%s-%s-000.png", enemyName.getCString(), anime[_type].name.getCString());
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


		switch (enemyType)
		{
		case enemyType::Aegis:
			switch (_type)
			{
			case 0: // wait
			case 1: // move
				this->runAction(rep);
				break;
			case 2: // attack
			{
				auto seq = Sequence::create(
					animate,
					CallFunc::create(CC_CALLBACK_0(EnemyAnimation::setAnimation, this, 0)),
					nullptr);
				this->runAction(seq);
			}
			break;
			case 3: // die1
			case 4: // die2 
			case 5: // die3
				this->runAction(animate);
				break;
			}
			break;
		}
	}
}
