#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "TestData.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode

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

	addLabelTimer(this, 10, wPos8 - Vec2(0, 10.0f), anc8);

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
			if (isLeft)
			{
				if (playerBox->getPositionX() > 400.0f)
					playerBox->setPositionX(playerBox->getPositionX() - 8.0f);
				else
					bgLayer->setPositionX(bgLayer->getPositionX() + 8.0f);

			}
			else if (!isLeft)
			{
				if (playerBox->getPositionX() < wSizeX - 400.0f)
					playerBox->setPositionX(playerBox->getPositionX() + 8.0f);
				else
					bgLayer->setPositionX(bgLayer->getPositionX() - 8.0f);
			}
			/*if (isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(5.0f, 0));
			else if (!isLeft && playerBox->getBoundingBox().intersectsRect(monsterBox->getBoundingBox()))
				playerBox->setPosition(playerBox->getPosition() + Vec2(-5.0f, 0));*/
		}
		if (isPressedUD)
		{
			if (isUp)
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, 3.0f));
			else if (!isUp)
				playerBox->setPosition(playerBox->getPosition() + Vec2(0, -3.0f));
		}
	}	

	float minX1 = bgLayer->getPositionX() + (bgSprite[0]->getPositionX() - bgSprite[0]->getContentSize().width * bgSprite[0]->getScaleX() / 2);
	float maxX1 = bgLayer->getPositionX() + (bgSprite[0]->getPositionX() + bgSprite[0]->getContentSize().width * bgSprite[0]->getScaleX() / 2);
	float minX2 = bgLayer->getPositionX() + (bgSprite[1]->getPositionX() - bgSprite[1]->getContentSize().width * bgSprite[1]->getScaleX() / 2);
	float maxX2 = bgLayer->getPositionX() + (bgSprite[1]->getPositionX() + bgSprite[1]->getContentSize().width * bgSprite[1]->getScaleX() / 2);
	float wZero = bgLayer->getPositionX() + (actLayer->getPositionX() - actLayer->getContentSize().width);
	
}

void HelloWorld::addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc)
{
	TTFConfig ttfConfig("fonts/hexgon.ttf", 40);
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
		int userTime = (int)(pLabel->getUserData()) - 1;
		pLabel->setString(StringUtils::format("Noel Vermillion - %d", userTime));

		if (userTime <= 0)
		{
			//이 구간에는, 시간이 0이 되었을때의 동작내용을 구현합니다.

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
		sPlayer->setFlippedX(true);
		if (!isPressedLR || !isPressedUD)
		{
			actCharacter(actList::Move);
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
			actCharacter(actList::Move);
			isPressedLR = true;
		}
		break;
	case KEY::KEY_W: // Up
	case KEY::KEY_UP_ARROW:
		isUp = true;
		isPressUp = true;
		if (!isPressedLR || !isPressedUD)
		{
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
			actCharacter(actList::Move);
			isPressedUD = true;
		}
		break;
	case KEY::KEY_1:
		actCharacter(actList::Attack);
		break;
	case KEY::KEY_2:
		sPlayer->isFlippedX() ? sPlayer->setFlippedX(false) : sPlayer->setFlippedX(true);
		actCharacter(actList::Victory);
		break;
	case KEY::KEY_3:
		actCharacter(actList::Die);
		break;
	case KEY::KEY_4:
		actCharacter(actList::Skill);
		break;
	case KEY::KEY_TAB:
		log("%f2", bgLayer->getPositionX() + (actLayer->getPositionX() - actLayer->getContentSize().width));
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
			sPlayer->setFlippedX(true);
		}
		if (!isPressLeft && !isPressRight)
		{
			if (!isPressedUD)
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
			if (!isPressedLR)
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
			if (!isPressedLR)
				actCharacter(actList::Wait);
			isPressedUD = false;
		}
		break;
	case KEY::KEY_TAB:
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

	setCharacter.init();

	actCharacter(actList::Wait);
}

void HelloWorld::actCharacter(int _type)
{
	setCharacter.setAnimation(sPlayer, _type);
}

double HelloWorld::getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni)
{
	double c = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	double t = c / _magni;
	
	return t;
}
