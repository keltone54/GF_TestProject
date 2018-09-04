#include "MainScene.h"
#include "GlobalDef.h"

#include "SecondScene.h"
#include "StartScene.h"
#include "PlayerCharacter.h"
#include "PopLayer.h"

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

	// 초기화 ====================================================

	//g_pTestData->init();

	initValue();
	initBackground();
	debugLabel();

	// 내용 ======================================================

	Noel = PlayerCharacter::create();
	Noel->setPosition(wPos5);
	actLayer->addChild(Noel);

	addLabelTimer(actLayer, -1, wPos8 - Vec2(0, 10.0f), anc8);

	testAnim();

	//============================================================
	
	initListener();
	return true;
}

//==========================================================

void MainScene::initListener()
{
	this->schedule(schedule_selector(MainScene::callEveryFrame));

	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);

	NotificationCenter::sharedNotificationCenter()->
		addObserver(this, callfuncO_selector(MainScene::doNotification), "popup", NULL);
}

void MainScene::initValue()
{
	bPaused = false;
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
	lblPosX = Label::createWithTTF(ttfconfg, "");
	lblPosX->setAnchorPoint(anc7);
	lblPosX->setPosition(wPos7 + Vec2(20, -20));
	actLayer->addChild(lblPosX);

	lblPosY = Label::createWithTTF(ttfconfg, "");
	lblPosY->setAnchorPoint(anc7);
	lblPosY->setPosition(lblPosX->getPosition() + Vec2(0, -30));
	actLayer->addChild(lblPosY);

	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory, 101);
}

void MainScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

//==========================================================

void MainScene::callEveryFrame(float f)
{
	if (bPaused)
	{
		bPaused = false;
	}

	displayMemory();

	if (Noel->isMoveBackground())
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

	lblPosX->setString(StringUtils::format("Pos X : %d", (int)(-bgLayer->getPositionX() + Noel->getPositionX()) / 10));
	lblPosY->setString(StringUtils::format("Pos Y : %d", (int)Noel->getPositionY() / 10));
}

//==========================================================

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (!bPaused)
	{
		switch (keyCode)
		{
		case KEY::KEY_TAB:
			moveToSecondScene(this);
			break;
		case KEY::KEY_GRAVE:
			doPop(this);
			break;
		case KEY::KEY_ESCAPE:
			Director::sharedDirector()->end();
			//g_pTestData->DeleteMemory();
			break;
		}
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
	if (pLabel && !bPaused)
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

void MainScene::moveToSecondScene(Ref* pSender)
{
	_eventDispatcher->removeAllEventListeners();
	NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	auto pScene = SecondScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	this->removeFromParentAndCleanup(true);
}

void MainScene::moveToStartScene(Ref* pSender)
{
	_eventDispatcher->removeAllEventListeners();
	NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	auto pScene = StartScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	this->removeFromParentAndCleanup(true);
}

//==========================================================

void MainScene::doPop(Ref* pSender)
{
	auto pPop = PopLayer::create();
	this->addChild(pPop, 100);
}

void MainScene::doNotification(Object* obj)
{
	auto pParam = (String*)obj;

	if (pParam->intValue() == 0) // Create
	{
		Noel->pauseAnimation();
		Noel->pauseSchedulerAndActions();
		bPaused = true;
		log("pause");
		//Director::sharedDirector()->pause();
		this->pauseSchedulerAndActions();
		this->getEventDispatcher()->pauseEventListenersForTarget(actLayer, true);
	}
	else if (pParam->intValue() == 1) // Close
	{
		Noel->resumeAnimation();
		Noel->resumeSchedulerAndActions();
		log("resume");
		//Director::sharedDirector()->resume();
		this->resumeSchedulerAndActions();
		this->getEventDispatcher()->resumeEventListenersForTarget(actLayer, true);
		
	}
	else if (pParam->intValue() == 2) // Move Scene
	{
		Noel->resumeAnimation();
		log("move to startscene");
		//Director::sharedDirector()->resume();
		moveToStartScene(this);
	}
	
}

void MainScene::testAnim()
{
	auto z = Sprite::create();
	z->setTextureRect(Rect(0, 0, 50, 50));
	z->setColor(Color3B::ORANGE);
	z->setOpacity(100);
	this->addChild(z);
	z->setPosition(wPos4 + Vec2(300,0));

	auto anim = MoveBy::create(1, Vec2(200,0));
	auto anim2 = anim->reverse();
	auto seq = Sequence::create(anim, anim2, nullptr);
	auto rep = RepeatForever::create(seq);
	z->runAction(rep);
}

//==========================================================
