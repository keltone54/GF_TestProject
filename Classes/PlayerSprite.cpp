#include "PlayerSprite.h"

USING_NS_CC;

enum actList
{
	Wait,
	Move,
	Attack,
	Die,
	Skill,
	Victory,
	VictoryLoop
};

void PlayerSprite::init()
{
	anime[0].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-wait.png");
	anime[1].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-move.png");
	anime[2].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-attack.png");
	anime[3].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-die.png");
	anime[4].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-skill.png");
	anime[5].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-victory.png");
	anime[6].texture = Director::getInstance()->getTextureCache()->addImage("GF/Noel/Noel-victoryloop.png");

	anime[0].maxFrame = 40;		anime[0].cols = 5;	anime[0].rows = 8;
	anime[1].maxFrame = 24;		anime[1].cols = 5;	anime[1].rows = 5;
	anime[2].maxFrame = 20;		anime[2].cols = 5;	anime[2].rows = 4;
	anime[3].maxFrame = 51;		anime[3].cols = 11;	anime[3].rows = 5;
	anime[4].maxFrame = 174;	anime[4].cols = 22;	anime[4].rows = 8;
	anime[5].maxFrame = 140;	anime[5].cols = 11;	anime[5].rows = 13;
	anime[6].maxFrame = 40;		anime[6].cols = 5;	anime[6].rows = 8;

	//"GF/Noel/Noel-wait.png",			40, 5, 8
	//"GF/Noel/Noel-move.png",			24, 5, 5
	//"GF/Noel/Noel-attack.png",		20, 5, 4
	//"GF/Noel/Noel-die.png",			51, 11, 5
	//"GF/Noel/Noel-skill.png",			174, 22, 8
	//"GF/Noel/Noel-victory.png",		140, 11, 13
	//"GF/Noel/Noel-victoryloop.png",	40, 5, 8
	
}

void PlayerSprite::setAnimation(cocos2d::Sprite* _sprite, int _type)
{
	_sprite->stopAllActions();

	auto anim = Animation::create();
	anim->setDelayPerUnit(0.025f);

	float wW = anime[_type].texture->getContentSize().width / anime[_type].cols;
	float wH = anime[_type].texture->getContentSize().height / anime[_type].rows;

	float ancX = 227.0f;
	float ancY = 70.0f;

	float aX = ancX / wW;
	float aY = ancY / wH;
	float faX = (wW - ancX) / wW;

	if (!_sprite->isFlippedX())
		_sprite->setAnchorPoint(Vec2(aX, aY));
	else
		_sprite->setAnchorPoint(Vec2(faX, aY));

	_sprite->setTexture(anime[_type].texture);
	_sprite->setTextureRect(Rect(0, 0, wW, wH));

	for (int i = 0; i < anime[_type].maxFrame; i++)
	{
		int col = i % anime[_type].cols;
		int row = i / anime[_type].cols;

		anim->addSpriteFrameWithTexture(
			anime[_type].texture, Rect(col * wW, row * wH, wW, wH));
	}

	auto ani = Animate::create(anim);
	auto rep = RepeatForever::create(ani);

	if(_type == actList::Wait || _type == actList::Move || _type == actList::VictoryLoop)
		_sprite->runAction(rep);
	else if (_type == actList::Attack || _type == actList::Skill)
	{
		auto seq = Sequence::create(ani, CallFunc::create(CC_CALLBACK_0(PlayerSprite::setAnimation, this, _sprite, actList::Wait)), nullptr);
		_sprite->runAction(seq);
	}
	else if (_type == actList::Victory)
	{
		auto seq = Sequence::create(ani, CallFunc::create(CC_CALLBACK_0(PlayerSprite::setAnimation, this, _sprite, actList::VictoryLoop)), nullptr);
		_sprite->runAction(seq);
	}
	else if (_type == Die)
	{
		_sprite->runAction(ani);
	}
}
