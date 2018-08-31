#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "TestData.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode

#define PLAYER_SPEED 8.0f

enum actList
{
	Wait,
	Move,
	Attack,
	Die,
	Victory,
	VictoryLoop
};

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	{
		if (!Scene::init()) return false;
		bgLayer = Layer::create();
		this->addChild(bgLayer);
		actLayer = Layer::create();
		this->addChild(actLayer);
	}

	// 내용 ======================================================

	//g_pTestData->init();

	initValue();
	initBackground();
	initCharacter();
	initPlayerBox();

	addLabelTimer(this, -1, wPos8 - Vec2(0, 10.0f), anc8);
	
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 24);
	lbl_PosX = Label::createWithTTF(ttfconfg, "");
	lbl_PosX->setAnchorPoint(anc7);
	lbl_PosX->setPosition(wPos7 + Vec2(20, -20));
	this->addChild(lbl_PosX);

	lbl_shootingCooldown = Label::createWithTTF(ttfconfg, "");
	lbl_shootingCooldown->setPosition(Vec2(playerBox->getContentSize().width / 2, playerBox->getContentSize().height + 30.0f));
	playerBox->addChild(lbl_shootingCooldown);
			
	//============================================================

	this->schedule(schedule_selector(HelloWorld::callEveryFrame));

	{
		auto K_listner = EventListenerKeyboard::create();
		K_listner->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
		K_listner->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);
	}

	//============================================================

	return true;
}

void HelloWorld::initValue()
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
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
}

void HelloWorld::onExit()
{
	Scene::onExit();
}

void HelloWorld::callEveryFrame(float f)
{
	if (!setNoel.isShooting() && !isPressSPC)
	{
		if (isPressedLR || isPressedUD)
		{
			if (isPressedLR)
			{
				if (isLeft)
				{
					if (playerBox->getPositionX() > 300.0f)
						playerBox->setPositionX(playerBox->getPositionX() - PLAYER_SPEED);
					else
						bgLayer->setPositionX(bgLayer->getPositionX() + PLAYER_SPEED);

					if (!sPlayer->isFlippedX())
						sPlayer->setFlippedX(true);
				}
				else if (!isLeft)
				{
					if (playerBox->getPositionX() < wSizeX - 300.0f)
						playerBox->setPositionX(playerBox->getPositionX() + PLAYER_SPEED);
					else
						bgLayer->setPositionX(bgLayer->getPositionX() - PLAYER_SPEED);

					if (sPlayer->isFlippedX())
						sPlayer->setFlippedX(false);
				}
				/*if (isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
					playerBox->setPosition(playerBox->getPosition() + Vec2(5.0f, 0));
				else if (!isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
					playerBox->setPosition(playerBox->getPosition() + Vec2(-5.0f, 0));*/
			}
			if (isPressedUD)
			{
				if (isUp)
					playerBox->setPosition(playerBox->getPosition() + Vec2(0, PLAYER_SPEED / 2));
				else if (!isUp)
					playerBox->setPosition(playerBox->getPosition() + Vec2(0, -PLAYER_SPEED / 2));
			}

			if (!isCanMove)
			{
				if (isPressedLR || isPressedUD)
					setNoel.setAnimation(sPlayer, actList::Move);
				else
					setNoel.setAnimation(sPlayer, actList::Wait);

				isCanMove = true;
			}
		}
	}

	//

	{
		float minX1 = bgLayer->getPositionX() + (bgSprite[0]->getPositionX() - bgSprite[0]->getContentSize().width * bgSprite[0]->getScaleX() / 2);
		float maxX1 = bgLayer->getPositionX() + (bgSprite[0]->getPositionX() + bgSprite[0]->getContentSize().width * bgSprite[0]->getScaleX() / 2);
		float minX2 = bgLayer->getPositionX() + (bgSprite[1]->getPositionX() - bgSprite[1]->getContentSize().width * bgSprite[1]->getScaleX() / 2);
		float maxX2 = bgLayer->getPositionX() + (bgSprite[1]->getPositionX() + bgSprite[1]->getContentSize().width * bgSprite[1]->getScaleX() / 2);

		// 배경 이미지 무한반복
		if (minX1 > 0 && minX2 > wSizeX) bgSprite[1]->setPositionX(bgSprite[1]->getPositionX() - wSizeX * 2);
		else if (maxX1 < wSizeX && maxX2 < 0) bgSprite[1]->setPositionX(bgSprite[1]->getPositionX() + wSizeX * 2);
		else if (minX2 > 0 && minX1 > wSizeX) bgSprite[0]->setPositionX(bgSprite[0]->getPositionX() - wSizeX * 2);
		else if (maxX2 < wSizeX && maxX1 < 0) bgSprite[0]->setPositionX(bgSprite[0]->getPositionX() + wSizeX * 2);
	}

	lbl_PosX->setString(StringUtils::format("Pos X : %d", (int)-bgLayer->getPositionX()));


	if (!setNoel.isShooting() && isPressSPC)
		actCharacter(actList::Attack);

	if (setNoel.isShooting())
		setNoel.runShootingCooldown();

	if(setNoel.isShooting())
		lbl_shootingCooldown->setString(StringUtils::format("%d", setNoel.getShootingCooldown()));
	else if (lbl_shootingCooldown->getString() != "")
		lbl_shootingCooldown->setString("");
}

void HelloWorld::addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc)
{
	TTFConfig ttfConfig("fonts/xenosphere.ttf", 40);
	auto pLabelTime = Label::createWithTTF(ttfConfig, "");
	pLabelTime->setUserData((int*)nTime);
	pLabelTime->setColor(Color3B::WHITE);
	pLabelTime->setAnchorPoint(anc);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);

	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(HelloWorld::updateLabel, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}

void HelloWorld::updateLabel(cocos2d::Label* pLabel)
{
	if (pLabel)
	{
		int userTime = (int)(pLabel->getUserData()) + 1;
		pLabel->setString(StringUtils::format("TIME\n%3d", userTime));

		if (userTime < 0)
		{
			pLabel->stopAllActions();
			return;
		}
		else
			pLabel->setUserData((int*)userTime);
	}
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case KEY::KEY_A: // Left
	case KEY::KEY_LEFT_ARROW:
		isLeft = true;
		isPressLeft = true;

		if (!isPressedLR || !isPressedUD)
		{
			if(isCanMove)
				actCharacter(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove)
				actCharacter(actList::Move);		
		break;
	case KEY::KEY_D: // Right
	case KEY::KEY_RIGHT_ARROW:
		isLeft = false;
		isPressRight = true;

		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				actCharacter(actList::Move);
			isPressedLR = true;
		}
		else if (isPressedLR && isPressedUD)
			if (isCanMove)
				actCharacter(actList::Move);
		break;
	case KEY::KEY_W: // Up
	case KEY::KEY_UP_ARROW:
		isUp = true;
		isPressUp = true;
		if (!isPressedLR || !isPressedUD)
		{
			if (isCanMove)
				actCharacter(actList::Move);
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
				actCharacter(actList::Move);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_E:
		sPlayer->isFlippedX() ? sPlayer->setFlippedX(false) : sPlayer->setFlippedX(true);
		actCharacter(actList::Victory);
		break;
	case KEY::KEY_Q:
		actCharacter(actList::Die);
		break;
	case KEY::KEY_SPACE:
		isPressSPC = true;
		isCanMove = false;
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		//g_pTestData->DeleteMemory();
		break;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
				actCharacter(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove)
				actCharacter(actList::Wait);
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
				actCharacter(actList::Move);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD && isCanMove)
				actCharacter(actList::Wait);
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
				actCharacter(actList::Wait);
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
				actCharacter(actList::Wait);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_SPACE:
		isPressSPC = false;
		break;
	}

}

void HelloWorld::initBackground()
{
	bgSprite[0] = Sprite::create("GF/Street.jpg");
	bgSprite[1] = Sprite::create("GF/Street.jpg");

	bgSprite[0]->setPosition(wPos5);
	bgSprite[0]->setScale(1.25f, 1.0f);
	bgSprite[1]->setPosition(wPos5 + Vec2(bgSprite[0]->getContentSize().width * bgSprite[0]->getScaleX(), 0));
	bgSprite[1]->setScale(1.25f, 1.0f);
	bgLayer->addChild(bgSprite[0]);
	bgLayer->addChild(bgSprite[1]);
}

void HelloWorld::initPlayerBox()
{
	playerBox = Sprite::create();
	//playerBox->setTextureRect(Rect(-50, -80, 50, 80));
	playerBox->setTextureRect(Rect(-50, -80, 50, 90));
	playerBox->setColor(Color3B::GREEN);
	playerBox->setOpacity(0.0f);
	playerBox->setPosition(wPos5);
	actLayer->addChild(playerBox);

	sPlayer->setPosition(Vec2(playerBox->getContentSize().width / 2, 0));
	sPlayer->setScale(0.65f);
	//sPlayer->setOpacity(50.0f);

	playerBox->setZOrder(101);
	playerBox->addChild(sPlayer);

	/*auto chkpos = Sprite::create();
	chkpos->setTextureRect(Rect(0, 0, 10, 10));
	chkpos->setColor((Color3B::RED));
	chkpos->setPosition(playerBox->getContentSize() / 2);
	playerBox->addChild(chkpos);*/
}

void HelloWorld::initCharacter()
{
	sPlayer = Sprite::create();

	actCharacter(actList::Wait);
}

void HelloWorld::actCharacter(int _type)
{
	setNoel.setAnimation(sPlayer, _type);
}

double HelloWorld::getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni)
{
	double c = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	double t = c / _magni;
	
	return t;
}
