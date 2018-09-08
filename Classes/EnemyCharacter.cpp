#include "EnemyCharacter.h"
#include "GlobalDef.h"

#include "EnemyAnimation.h"

bool EnemyCharacter::init(int _enemyType)
{
	if (!Node::init()) return false;
	//============================================================

	enemyType = _enemyType;
	this->getActionManager();
	initCharacter();
	initValue();
	debugLabel();

	//============================================================
	initListener();
	return true;
}

void EnemyCharacter::initCharacter()
{
	bodyBox = Sprite::create();
	this->addChild(bodyBox, 11);

	crtAnim = EnemyAnimation::create(enemyType);

	crtAnim->setAnimation(0);
	bodyBox->addChild(crtAnim);

	bodyBox->setTextureRect(Rect(-50, -80, 50, 90));
	bodyBox->setColor(Color3B::GREEN);
	//bodyBox->setOpacity(0);

	crtAnim->setPosition(Vec2(bodyBox->getContentSize().width / 2, 0));
	crtAnim->setScale(0.65f);
	//sPlayer->setOpacity(50.0f);
}

void EnemyCharacter::initListener()
{

}

void EnemyCharacter::initValue()
{
}

void EnemyCharacter::debugLabel()
{
}

void EnemyCharacter::callEveryFrame(float f)
{
}

void EnemyCharacter::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void EnemyCharacter::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}
