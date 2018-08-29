#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "TestData.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode

enum sltChar
{
	Noel,
	G11
};

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	{
		if (!Scene::init()) return false;
		auto wlayer = LayerColor::create(Color4B::WHITE);
		this->addChild(wlayer);
	}

	// 내용 ======================================================

	//merong

	//g_pTestData->init();
	this->schedule(schedule_selector(HelloWorld::callEveryFrame));

	initValue();
	initBackground();

	initCharacter(sltChar::Noel);

	playerBox = Sprite::create();
	playerBox->setTextureRect(Rect(-50, -80, 50, 80));
	playerBox->setColor(Color3B::GREEN);
	playerBox->setOpacity(0.0f);
	playerBox->setPosition(wPos5);
	this->addChild(playerBox);

	sPlayer->setPosition(Vec2(playerBox->getContentSize().width / 2, playerBox->getContentSize().height / 2));
	sPlayer->setScale(1.0f);
	playerBox->setZOrder(101);
	playerBox->addChild(sPlayer);



	initMonster();

	monsterBox = Sprite::create();
	monsterBox->setTextureRect(Rect(-50, -100, 50, 100));
	monsterBox->setColor(Color3B::RED);
	monsterBox->setOpacity(0.0f);
	monsterBox->setPosition(wPos5 + Vec2(100, 0));
	this->addChild(monsterBox);

	sMonster->setPosition(Vec2(monsterBox->getContentSize().width / 2, monsterBox->getContentSize().height / 2));
	sMonster->setScale(1.0f);
	monsterBox->setZOrder(100);
	monsterBox->setScale(0.75f);
	monsterBox->addChild(sMonster);

	//============================================================

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

	chaseOn = false;
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
	if (isPressedLR || isPressedUD)
	{
		if (isPressedLR)
		{
			if (isLeft && !playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(-5.0f, 0));
			else if (!isLeft && !playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(5.0f, 0));
			
			if (isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(5.0f, 0));
			else if (!isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(-5.0f, 0));
		}
		if (isPressedUD)
		{
			if (isUp && !playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, 3.0f));
			else if (!isUp && !playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, -3.0f));

			if (isUp && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, -3.0f));
			else if (!isUp && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, 3.0f));
		}
	}

	if (chaseOn)
	{

	}

	if (playerBox->getPosition().x > monsterBox->getPosition().x)
	{
		sMonster->setFlippedX(true);
	}
	else if (playerBox->getPosition().x < monsterBox->getPosition().x)
	{
		sMonster->setFlippedX(false);
	}
}

void HelloWorld::addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc)
{
	auto pLabelTime = Label::create("", "Arial", 32);
	pLabelTime->setUserData((int*)nTime);
	pLabelTime->setColor(Color3B::BLACK);
	pLabelTime->setAnchorPoint(anc);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);

	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(HelloWorld::upddateLabel, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}

void HelloWorld::upddateLabel(cocos2d::Label* pLabel)
{
	if (pLabel)
	{
		int userTime = (int)(pLabel->getUserData());
		pLabel->setString(StringUtils::format("%d초 후 이동", userTime));

		if (userTime <= 0)
		{
			//이 구간에는, 시간이 0이 되었을때의 동작내용을 구현합니다.

			pLabel->stopAllActions();
			log("timer End");
			return;
		}

		userTime -= 1;

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
		sPlayer->setFlippedX(true);
		if (!isPressedLR || !isPressedUD)
		{
			moveCharacter(n_sltChar);
			isPressedLR = true;
		}
		break;
	case KEY::KEY_D: // Right
	case KEY::KEY_RIGHT_ARROW:
		isLeft = false;
		isPressRight = true;
		sPlayer->setFlippedX(false);
		if (!isPressedLR || !isPressedUD)
		{
			moveCharacter(n_sltChar);
			isPressedLR = true;
		}
		break;
	case KEY::KEY_W: // Up
	case KEY::KEY_UP_ARROW:
		isUp = true;
		isPressUp = true;
		if (!isPressedLR || !isPressedUD)
		{
			moveCharacter(n_sltChar);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_S: // Down
	case KEY::KEY_DOWN_ARROW:
		isUp = false;
		isPressDown = true;
		if (!isPressedLR || !isPressedUD)
		{
			moveCharacter(n_sltChar);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_TAB:
		if (isPressedLR || isPressedUD)
		{
			n_sltChar == sltChar::Noel ? n_sltChar = sltChar::G11 : n_sltChar = sltChar::Noel;
			moveCharacter(n_sltChar);
		}
		else
		{
			n_sltChar == sltChar::Noel ? n_sltChar = sltChar::G11 : n_sltChar = sltChar::Noel;
			waitCharacter(n_sltChar);
		}
		break;
	case KEY::KEY_SPACE:
		chaseOn = true;
		monsterBox->stopAllActions();
		mAction_MoveTo = MoveTo::create(getDistance(playerBox->getPosition(), monsterBox->getPosition(), 50), playerBox->getPosition());
		monsterBox->runAction(mAction_MoveTo);
		moveMonster();
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
			sPlayer->setFlippedX(false);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD)
				waitCharacter(n_sltChar);
			isPressedLR = false;
		}
		break;
	case KEY::KEY_D:
	case KEY::KEY_RIGHT_ARROW:
		isPressRight = false;
		if (isPressLeft)
		{
			isLeft = true;
			sPlayer->setFlippedX(true);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD)
				waitCharacter(n_sltChar);
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
			if (!isPressedLR)
				waitCharacter(n_sltChar);
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
			if (!isPressedLR)
				waitCharacter(n_sltChar);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_TAB:
		break;
	}

}

void HelloWorld::initBackground()
{
	auto bg_street = Sprite::create("GF/Street.jpg");
	bg_street->setPosition(wPos5);
	bg_street->setScale(2.5f, 2.0f);
	this->addChild(bg_street);
}

void HelloWorld::initCharacter(int _sltChar)
{
	n_sltChar = _sltChar;

	sPlayer = Sprite::create();

	switch (_sltChar)
	{
	case sltChar::Noel:
		setCharacter.setAnimation(sPlayer, "GF/Noel/Noel-wait.png", 40, 6, 7);
		break;
	case sltChar::G11:
		setCharacter.setAnimation(sPlayer, "GF/G11/G11-wait.png", 54, 6, 9);
		break;
	}
}

void HelloWorld::moveCharacter(int _sltChar)
{
	switch (_sltChar)
	{
	case sltChar::Noel:
		setCharacter.setAnimation(sPlayer, "GF/Noel/Noel-move.png", 24, 5, 5);
		break;
	case sltChar::G11:
		setCharacter.setAnimation(sPlayer, "GF/G11/G11-move.png", 24, 5, 5);
		break;
	}
}

void HelloWorld::waitCharacter(int _sltChar)
{
	switch (_sltChar)
	{
	case sltChar::Noel:
		setCharacter.setAnimation(sPlayer, "GF/Noel/Noel-wait.png", 40, 6, 7);
		break;
	case sltChar::G11:
		setCharacter.setAnimation(sPlayer, "GF/G11/G11-wait.png", 54, 6, 9);
		break;
	}
}

void HelloWorld::initMonster()
{
	sMonster = Sprite::create();

	setMonster.setAnimation(sMonster, "GF/Zombie/Zombie-wait.png", 107, 11, 10);
}

void HelloWorld::moveMonster()
{
	setMonster.setAnimation(sMonster, "GF/Zombie/Zombie-move.png", 80, 9, 9);
}

void HelloWorld::waitMonster()
{
	setMonster.setAnimation(sMonster, "GF/Zombie/Zombie-wait.png", 107, 11, 10);
}

double HelloWorld::getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni)
{
	double c = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	double t = c / _magni;
	
	return t;
}
