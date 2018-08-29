#include "Character.h"

USING_NS_CC;

void Character::init(int _type, cocos2d::Sprite * _sprite)
{
	switch (_type)
	{
	case crType::PLAYER:
		_sprite = Sprite::create();
		break;
	case crType::NPC:
		break;
	case crType::MONSTER:
		break;
	}
}

void Character::setAnimation(cocos2d::Sprite * _sprite, std::string _file, int _maxFrame, int _cols, int _rows)
{
	_sprite->stopAllActions();

	auto texture = Director::getInstance()->getTextureCache()->addImage(_file);

	auto anim = Animation::create();
	anim->setDelayPerUnit(0.025f);

	float wW = texture->getContentSize().width / _cols;
	float wH = texture->getContentSize().height / _rows;

	_sprite->setTexture(texture);
	_sprite->setTextureRect(Rect(0, 0, wW, wH));

	for (int i = 0; i < _maxFrame; i++)
	{
		int col = i % _cols;
		int row = i / _cols;

		anim->addSpriteFrameWithTexture(
			texture, Rect(col * wW, row * wH, wW, wH));
	}

	auto ani = Animate::create(anim);
	auto rep = RepeatForever::create(ani);

	_sprite->runAction(rep);
}
