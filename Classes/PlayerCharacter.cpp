#include "PlayerCharacter.h"
#include "GlobalDef.h"
#include "PlayerAnimation.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode
#define PLAYER_SPEED 8.0f

//==========================================================

PlayerCharacter::PlayerCharacter()
{
	initCharacter();
	initValue();
	debugLabel();

	{
		this->schedule(schedule_selector(PlayerCharacter::callEveryFrame));

		auto K_listner = EventListenerKeyboard::create();
		K_listner->onKeyPressed = CC_CALLBACK_2(PlayerCharacter::onKeyPressed, this);
		K_listner->onKeyReleased = CC_CALLBACK_2(PlayerCharacter::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);
	}
}

//==========================================================

void PlayerCharacter::initCharacter()
{
	bodyBox = Sprite::create();
	this->addChild(bodyBox);

	crtAnim = PlayerAnimation::create();
	crtAnim->setAnimation(actList::Wait);
	bodyBox->addChild(crtAnim);

	bodyBox->setTextureRect(Rect(-50, -80, 50, 80));
	//bodyBox->setTextureRect(Rect(-50, -80, 50, 90));
	bodyBox->setColor(Color3B::GREEN);
	bodyBox->setOpacity(0.0f);

	crtAnim->setPosition(Vec2(bodyBox->getContentSize().width / 2, 0));
	crtAnim->setScale(0.65f);
	//sPlayer->setOpacity(50.0f);


	/*auto chkpos = Sprite::create();
	chkpos->setTextureRect(Rect(0, 0, 10, 10));
	chkpos->setColor((Color3B::RED));
	chkpos->setPosition(playerBox->getContentSize() / 2);
	playerBox->addChild(chkpos);*/
}

void PlayerCharacter::initValue()
{
	isPressedLR = false;
	isLeft = false;
	isPressLeft = false;
	isPressRight = false;

	isPressedUD = false;
	isUp = false;
	isPressUp = false;
	isPressDown = false;

	isPressSPC = false;

	isCanMove = true;

	isMoveBG = false;
}

void PlayerCharacter::debugLabel()
{
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 24);
	lbl_shootingCooldown = Label::createWithTTF(ttfconfg, "");
	lbl_shootingCooldown->setPosition(Vec2(bodyBox->getContentSize().width / 2, bodyBox->getContentSize().height + 30.0f));
	bodyBox->addChild(lbl_shootingCooldown);
}

//==========================================================

void PlayerCharacter::callEveryFrame(float f)
{

	if (!crtAnim->isShooting() && !isPressSPC)
	{
		if (isPressedLR || isPressedUD)
		{
			if (isPressedLR)
			{
				if (isLeft)
				{
					if (this->getPositionX() > 300.0f)
						this->setPositionX(this->getPositionX() - PLAYER_SPEED);
					else if (!isMoveBG)
						isMoveBG = true;

					if (!crtAnim->isFlippedX())
						crtAnim->setFlippedX(true);
				}
				else if (!isLeft)
				{
					if (this->getPositionX() < wSizeX - 300.0f)
						this->setPositionX(this->getPositionX() + PLAYER_SPEED);
					else if (!isMoveBG)
						isMoveBG = true;

					if (crtAnim->isFlippedX())
						crtAnim->setFlippedX(false);
				}
				/*if (isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(5.0f, 0));
				else if (!isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(-5.0f, 0));*/
			}
			if (isPressedUD)
			{
				if (isUp)
					bodyBox->setPosition(bodyBox->getPosition() + Vec2(0, PLAYER_SPEED / 2));
				else if (!isUp)
					bodyBox->setPosition(bodyBox->getPosition() + Vec2(0, -PLAYER_SPEED / 2));
			}

			if (!isCanMove)
			{
				if (isPressedLR || isPressedUD)
					crtAnim->setAnimation(actList::Move);
				else
					crtAnim->setAnimation(actList::Wait);

				isCanMove = true;
			}
		}
	}
	else if (!crtAnim->isShooting() && isPressSPC)
	{
		crtAnim->setAnimation(actList::Attack);
	}
	else if (crtAnim->isShooting())
	{
		crtAnim->runShootingCooldown();

		if(crtAnim->isShooting())
			lbl_shootingCooldown->setString(StringUtils::format("%d", crtAnim->getShootingCooldown()));
		else if (lbl_shootingCooldown->getString() != "")
			lbl_shootingCooldown->setString("");
	}

}

void PlayerCharacter::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_A: // Left
	case KEY::KEY_LEFT_ARROW:
		isLeft = true;
		isPressLeft = true;

		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
		break;
	case KEY::KEY_D: // Right
	case KEY::KEY_RIGHT_ARROW:
		isLeft = false;
		isPressRight = true;

		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
		break;
	case KEY::KEY_W: // Up
	case KEY::KEY_UP_ARROW:
		isUp = true;
		isPressUp = true;
		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_S: // Down
	case KEY::KEY_DOWN_ARROW:
		isUp = false;
		isPressDown = true;
		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_E:
		crtAnim->isFlippedX() ? crtAnim->setFlippedX(false) : crtAnim->setFlippedX(true); // chk
		crtAnim->setAnimation(actList::Victory);
		break;
	case KEY::KEY_Q:
		crtAnim->setAnimation(actList::Die);
		break;
	case KEY::KEY_SPACE:
		isPressSPC = true;
		isCanMove = false;
		break;
	}
}

void PlayerCharacter::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_A:
	case KEY::KEY_LEFT_ARROW:
		isPressLeft = false;
		if (isPressRight)
		{
			isLeft = false;
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove)
				crtAnim->setAnimation(actList::Wait);
			isPressedLR = false;
		}
		break;
	case KEY::KEY_D:
	case KEY::KEY_RIGHT_ARROW:
		isPressRight = false;
		if (isPressLeft)
		{
			isLeft = true;
			if (isCanMove)
				crtAnim->setAnimation(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove)
				crtAnim->setAnimation(actList::Wait);
			isPressedLR = false;
		}
		break;
	case KEY::KEY_W:
	case KEY::KEY_UP_ARROW:
		isPressUp = false;
		if (isPressDown)
		{
			isUp = false;
		}
		if (!isPressUp && !isPressDown)
		{
			if (!isPressedLR && isCanMove)
				crtAnim->setAnimation(actList::Wait);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_S:
	case KEY::KEY_DOWN_ARROW:
		isPressDown = false;
		if (isPressUp)
		{
			isUp = true;
		}
		if (!isPressUp && !isPressDown)
		{
			if (!isPressedLR && isCanMove)
				crtAnim->setAnimation(actList::Wait);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_SPACE:
		isPressSPC = false;
		break;
	}
}

//==========================================================

bool PlayerCharacter::isMoveBackground()
{
	if (isMoveBG)
		return true;
	else
		return false;
}

float PlayerCharacter::getMoveBackground()
{
	isMoveBG = false;
	if (crtAnim->isFlippedX())
		return PLAYER_SPEED;
	else
		return -PLAYER_SPEED;
}
