#include "PlayerCharacter.h"
#include "GlobalDef.h"

#include "PlayerAnimation.h"
#include "Bullet.h"

#define PLAYER_SPEED 8.0f

//==========================================================

bool PlayerCharacter::init()
{
	if (!Node::init()) return false;
	//============================================================

	initCharacter();
	initValue();
	debugLabel();

	//============================================================
	initListener();
	return true;
}

//==========================================================

void PlayerCharacter::initCharacter()
{
	bodyBox = Sprite::create();
	this->addChild(bodyBox, 1);

	crtAnim = PlayerAnimation::create();
	crtAnim->setAnimation(actList::Wait);
	bodyBox->addChild(crtAnim);

	bodyBox->setTextureRect(Rect(-50, -80, 50, 90));
	bodyBox->setColor(Color3B::GREEN);
	bodyBox->setOpacity(0);

	crtAnim->setPosition(Vec2(bodyBox->getContentSize().width / 2, 0));
	crtAnim->setScale(0.65f);
	//sPlayer->setOpacity(50.0f);

	bullet.clear();

	/*auto chkpos = Sprite::create();
	chkpos->setTextureRect(Rect(0, 0, 10, 10));
	chkpos->setColor((Color3B::RED));
	chkpos->setPosition(playerBox->getContentSize() / 2);
	playerBox->addChild(chkpos);*/
}

void PlayerCharacter::initListener()
{
	this->schedule(schedule_selector(PlayerCharacter::callEveryFrame));

	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PlayerCharacter::onKeyPressed, this);
	Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(PlayerCharacter::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
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
	isPressShift = false;

	isCanMove = true;

	isMoveBG = false;

	isPaused = false;
}

void PlayerCharacter::debugLabel()
{
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 24);
	lbl_TopHead = Label::createWithTTF(ttfconfg, "");
	lbl_TopHead->setPosition(Vec2(bodyBox->getContentSize().width / 2, bodyBox->getContentSize().height + 30.0f));
	bodyBox->addChild(lbl_TopHead);
}

//==========================================================

void PlayerCharacter::callEveryFrame(float f)
{
	
	if (!crtAnim->isShooting() && !crtAnim->isMGRunning() && !isPressSPC && !isPressShift)
	{
		if (isPressedLR || isPressedUD)
		{
			if (isPressedLR)
			{
				if (isLeft)
				{
					if (this->getPositionX() > 300.0f)
					{
						this->setPositionX(this->getPositionX() - PLAYER_SPEED);
						for (int i = 0; i < bullet.size(); i++)
							bullet[i]->setPositionX(bullet[i]->getPositionX() + PLAYER_SPEED);

					}
					else if (!isMoveBG)
					{
						isMoveBG = true;
						for (int i = 0; i < bullet.size(); i++)
							bullet[i]->setPositionX(bullet[i]->getPositionX() + PLAYER_SPEED);
					}

					if (!crtAnim->isFlippedX())
						crtAnim->setFlippedX(true);
				}
				else if (!isLeft)
				{
					if (this->getPositionX() < wSizeX - 300.0f)
					{
						this->setPositionX(this->getPositionX() + PLAYER_SPEED);
						for (int i = 0; i < bullet.size(); i++)
							bullet[i]->setPositionX(bullet[i]->getPositionX() - PLAYER_SPEED);
					}
					else if (!isMoveBG)
					{
						isMoveBG = true;
						for (int i = 0; i < bullet.size(); i++)
							bullet[i]->setPositionX(bullet[i]->getPositionX() - PLAYER_SPEED);
					}
					

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
				if (isUp && (this->getPositionY() < wSizeY - 220.0f))
				{
					this->setPositionY(this->getPositionY() + PLAYER_SPEED / 2);
					for(int i = 0; i < bullet.size();i++)
						bullet[i]->setPositionY(bullet[i]->getPositionY() - PLAYER_SPEED / 2);
				}
				else if (!isUp && (this->getPositionY() > 130.0f))
				{
					this->setPositionY(this->getPositionY() - PLAYER_SPEED / 2);
					for (int i = 0; i < bullet.size(); i++)
						bullet[i]->setPositionY(bullet[i]->getPositionY() + PLAYER_SPEED / 2);
				}
			}
		}
		if (!isCanMove && !isPaused)
		{
			if (isPressedLR || isPressedUD)
				crtAnim->setAnimation(actList::Move);
			else
				crtAnim->setAnimation(actList::Wait);

			isCanMove = true;
		}
	}
	else if (!crtAnim->isShooting() && !crtAnim->isMGRunning() && isPressSPC && !isPaused)
		crtAnim->setAnimation(actList::shotA);
	else if (crtAnim->isShooting() && !isPaused)
		crtAnim->runShootingCooldown();
	else if (!crtAnim->isMGRunning() && !crtAnim->isMGShootingRun() && isPressShift && !isPaused)
		crtAnim->setAnimation(actList::mgA);
	else if (crtAnim->isMGRunning() && !crtAnim->isMGShootingRun() && !crtAnim->getMGPhase() && !isPaused)
		crtAnim->runMGStartDelay();
	else if (crtAnim->isMGRunning() && !crtAnim->isMGShootingRun() && crtAnim->getMGPhase() && !isPaused)
		crtAnim->runMGEndDelay();
	else if (crtAnim->isMGRunning() && crtAnim->isMGShootingRun() && isPressShift && !isPaused)
	{
		crtAnim->setAnimation(actList::mgB);
		crtAnim->runMGInterval();
	}
	else if (crtAnim->isMGRunning() && crtAnim->isMGShootingRun() && !isPressShift && !isPaused)
		crtAnim->setAnimation(actList::mgC);
	if(crtAnim->isShooting() && crtAnim->getShootingCooldown() == 5)
		BulletCreate(bltType::HG);
	if (crtAnim->getMGInterval() == 3)
		BulletCreate(bltType::RF);
	if (bullet.size() != 0)
		Rect rct = bullet[0]->getBoundingBox();

	//==================================================================================
	//if (bullet.size() != 0 && lbl_TopHead->getString() != std::to_string(bullet.size()))
	//	lbl_TopHead->setString(StringUtils::format("%d", bullet.size()));
	//else if (bullet.size() == 0 && lbl_TopHead->getString() != "")
	//	lbl_TopHead->setString("");
	//==================================================================================

	for (int i = 0; i < bullet.size(); i++)
	{
		//if (v[i]->getBoundingBox().intersectsRect(Noel->getHitBox()) || !v[i]->isVisible())
		if (!bullet[i]->isVisible())
		{
			bullet[i]->removeFromParentAndCleanup(true);
			bullet[i] = nullptr;
			bullet.erase(bullet.begin() + i);
		}
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
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
		break;
	case KEY::KEY_D: // Right
	case KEY::KEY_RIGHT_ARROW:
		isLeft = false;
		isPressRight = true;

		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
		break;
	case KEY::KEY_W: // Up
	case KEY::KEY_UP_ARROW:
		isUp = true;
		isPressUp = true;
		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove && !isPaused)
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
			if (isCanMove && !isPaused)
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
	case KEY::KEY_Z:
		crtAnim->setAnimation(actList::Attack);
		break;
	case KEY::KEY_SPACE:
		isPressSPC = true;
		isCanMove = false;
		break;
	case KEY::KEY_SHIFT:
		isPressShift = true;
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
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove && !isPaused)
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
			if (isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove && !isPaused)
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
			if (!isPressedLR && isCanMove && !isPaused)
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
			if (!isPressedLR && isCanMove && !isPaused)
				crtAnim->setAnimation(actList::Wait);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_SPACE:
		isPressSPC = false;
		break;
	case KEY::KEY_SHIFT:
		isPressShift = false;
		break;
	}
}

//==========================================================

float PlayerCharacter::getMoveBackground()
{
	isMoveBG = false;
	if (crtAnim->isFlippedX())
		return PLAYER_SPEED;
	else
		return -PLAYER_SPEED;
}

//==========================================================

void PlayerCharacter::pauseAnimation()
{
	crtAnim->pause(); isPaused = true;
}

void PlayerCharacter::resumeAnimation()
{
	crtAnim->resume();

	isPaused = false;

	if (!isPressedLR && !isPressedUD && !crtAnim->isShooting() && !crtAnim->isMGRunning())
		crtAnim->setAnimation(actList::Wait);
	else if ((isPressedLR || isPressedUD) && !crtAnim->isShooting() && !crtAnim->isMGRunning())
		crtAnim->setAnimation(actList::Move);
}

//==========================================================

bool PlayerCharacter::getFlipedX()
{
	return crtAnim->isFlippedX();
}

//==========================================================

int PlayerCharacter::getShootingCoolDown()
{
	return crtAnim->getShootingCooldown();
}

bool PlayerCharacter::isShooting()
{
	return crtAnim->isShooting();
}

//==========================================================

void PlayerCharacter::BulletCreate(int _type)
{
	auto blt = Bullet::create();
	this->addChild(blt);
	blt->SetBulletType(_type);
	blt->setFlippedX(getFlipedX());

	if (_type == 0)
	{
		blt->SetBulletSpeed(0.75);
		blt->setPosition(blt->getPosition() + Vec2(0, 6));
	}
	else if (_type == 1)
	{
		blt->SetBulletSpeed(0.5);
		blt->setScale(0.8);
		if (!blt->isFlippedX())
			blt->setPosition(blt->getPosition() + Vec2(50, -22));
		else
			blt->setPosition(blt->getPosition() + Vec2(-50, -22));
		
	}

	blt->BulletCreate();
	bullet.push_back(blt);
}

std::vector<Bullet*>* PlayerCharacter::BulletGroup()
{
	return &bullet;
}

Bullet* PlayerCharacter::BulletSprite(int n)
{
	return bullet[n];
}

void PlayerCharacter::RemoveBullet(int n)
{
	if (bullet.size() >= n)
	{
		bullet[n]->stopAllActions();
		bullet[n]->removeFromParentAndCleanup(true);
		bullet[n] = nullptr;
		bullet.erase(bullet.begin() + n);

	}

}

//==========================================================
