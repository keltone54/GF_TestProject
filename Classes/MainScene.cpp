#include "MainScene.h"
#include "GlobalDef.h"

#include "SecondScene.h"
#include "TestData.h"
#include "PlayerCharacter.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode

Scene* MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init()) return false;

	// 레이어 ====================================================

	bgLayer = Layer::create();
	this->addChild(bgLayer);
	actLayer = Layer::create();
	this->addChild(actLayer);

	// 내용 ======================================================

	//g_pTestData->init();

	Noel = PlayerCharacter::create();
	Noel->setPosition(wPos5);
	actLayer->addChild(Noel);

	initValue();
	initBackground();

	addLabelTimer(this, -1, wPos8 - Vec2(0, 10.0f), anc8);
	
	debugLabel();
			
	//============================================================

	{
		this->schedule(schedule_selector(MainScene::callEveryFrame));

		auto Keyboard_Listener = EventListenerKeyboard::create();
		Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
		Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	}

	//============================================================

	return true;
}

//==========================================================

void MainScene::initValue()
{

}

void MainScene::initBackground()
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

void MainScene::debugLabel()
{
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 24);
	lbl_PosX = Label::createWithTTF(ttfconfg, "");
	lbl_PosX->setAnchorPoint(anc7);
	lbl_PosX->setPosition(wPos7 + Vec2(20, -20));
	this->addChild(lbl_PosX);
}

//==========================================================

void MainScene::callEveryFrame(float f)
{
	if(Noel->isMoveBackground())
		bgLayer->setPositionX(bgLayer->getPositionX() + Noel->getMoveBackground());

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
}

//==========================================================

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case KEY::KEY_TAB:
		moveToSecondScene(this);
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		//g_pTestData->DeleteMemory();
		break;
	}
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	
	}
}

//==========================================================

void MainScene::addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc)
{
	TTFConfig ttfConfig("fonts/xenosphere.ttf", 40);
	auto pLabelTime = Label::createWithTTF(ttfConfig, "");
	pLabelTime->setUserData((int*)nTime);
	pLabelTime->setColor(Color3B::WHITE);
	pLabelTime->setAnchorPoint(anc);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);

	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(MainScene::updateLabel, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}

void MainScene::updateLabel(cocos2d::Label* pLabel)
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

//==========================================================

double MainScene::getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni)
{
	double c = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	double t = c / _magni;
	
	return t;
}

void MainScene::moveToSecondScene(Ref * pSender)
{
	auto pScene = SecondScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
}
