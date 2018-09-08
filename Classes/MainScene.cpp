#include "MainScene.h"
#include "GlobalDef.h"

#include "SecondScene.h"
#include "StartScene.h"
#include "PlayerCharacter.h"
#include "PopPause.h"
#include "Bullet.h"

#include "EnemyCharacter.h"

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

	initValue();
	initBackground();
	debugLabel();
	
	// 내용 ======================================================

	Noel = PlayerCharacter::create();
	Noel->setPosition(wPos5);
	actLayer->addChild(Noel);

	createMob(10);	

	addLabelTimer(actLayer, -1, wPos8 - Vec2(0, 10.0f), anc8);

	//============================================================
	createNoti(MainScene, "popup", notiAction, this);
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

	if (Noel->isMoveBackground()) bgLayer->setPositionX(bgLayer->getPositionX() + Noel->getMoveBackground());
	
	bulletCollision();
	loopBG();

	for (int i = 0; i < Mob.size(); i++)
	{
		if (!Mob[i]->isDead())
			Mob[i]->setTargetPosition(Vec2(-bgLayer->getPositionX() + Noel->getPositionX(), Noel->getPositionY()));
	}

	//lblPosX->setString(StringUtils::format("Pos X : %d", (int)(-bgLayer->getPositionX() + Noel->getPositionX()) / 10));
	//lblPosY->setString(StringUtils::format("Pos Y : %d", (int)Noel->getPositionY() / 10));

	lblPosX->setString(StringUtils::format("Mob : %d", Mob.size()));
}

//==========================================================

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!bPaused)
	{
		switch (keyCode)
		{
		case KEY::KEY_F:
			removeTestBox();
			setTestBox();
			break;
		case KEY::KEY_G:
			removeTestBox();
			break;
		case KEY::KEY_1:
			for(int i = 0; i < Mob.size();i++)
				Mob[i]->order(enemyOrder::Wait_);
			break;
		case KEY::KEY_2:
			for (int i = 0; i < Mob.size(); i++)
				Mob[i]->order(enemyOrder::Chase_);
			break;
		case KEY::KEY_3:
			for (int i = 0; i < Mob.size(); i++)
				Mob[i]->order(enemyOrder::Attack_);
			break;
		case KEY::KEY_C:
			createMob(3);
			break;
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

void MainScene::loopBG()
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
	deleteAllNoti(this);
	auto pScene = StartScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	this->removeFromParentAndCleanup(true);
}

//==========================================================

void MainScene::doPop(Ref* pSender)
{
	auto pPop = PopPause::create();
	this->addChild(pPop);
}

void MainScene::notiAction(Object* obj)
{
	auto pParam = (String*)obj;

	if (pParam->intValue() == 0) // Create
	{
		Noel->pauseAnimation();
		Noel->pause();
		Noel->getEventDispatcher()->resumeEventListenersForTarget(Noel, true);
		bPaused = true;
		log("pause");
		this->pauseSchedulerAndActions();
		
		for(int i = 0; i < Noel->BulletGroup()->size();i++)
			this->getActionManager()->pauseTarget(Noel->BulletGroup()->at(i));
	}
	else if (pParam->intValue() == 1) // Close
	{
		resumeDelay();
	}
	else if (pParam->intValue() == 2) // Move Scene
	{
		log("move to startscene");
		moveToStartScene(this);
	}
}

void MainScene::resumeDelay()
{
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 128);
	auto n3 = Label::createWithTTF(ttfconfg, "3");
	auto n2 = Label::createWithTTF(ttfconfg, "2");
	auto n1 = Label::createWithTTF(ttfconfg, "1");
	this->addChild(n3);
	this->addChild(n2);
	this->addChild(n1);
	n3->setPosition(wPos5);
	n2->setPosition(wPos5);
	n1->setPosition(wPos5);
	n3->setVisible(false);
	n2->setVisible(false);
	n1->setVisible(false);

	auto spawn = Spawn::create(
		Show::create(),
		FadeOut::create(0.3),
		ScaleBy::create(0.3, 1.5),
		nullptr);
	auto seq3 = Sequence::create(spawn,
		RemoveSelf::create(true), nullptr);
	auto seq2 = Sequence::create(DelayTime::create(0.3),
		spawn,
		RemoveSelf::create(true), nullptr);
	auto seq1 = Sequence::create(DelayTime::create(0.6),
		spawn,
		CallFunc::create(CC_CALLBACK_0(MainScene::resumeAction, this)),
		RemoveSelf::create(true), nullptr);
	n3->runAction(seq3);
	n2->runAction(seq2);
	n1->runAction(seq1);
}

void MainScene::resumeAction()
{
	Noel->resume();
	Noel->resumeAnimation();
	log("resume");
	//Director::sharedDirector()->resume();
	this->resumeSchedulerAndActions();
	//this->getEventDispatcher()->resumeEventListenersForTarget(actLayer, true);
	for (int i = 0; i < Noel->BulletGroup()->size(); i++)
		this->getActionManager()->resumeTarget(Noel->BulletGroup()->at(i));
}

void MainScene::setTestBox()
{
	for (int i = 0; i < 200; i++)
	{
		auto tbox = Sprite::create();
		tbox->setTextureRect(Rect(0, 0, 20, 18));
		bgLayer->addChild(tbox);
		tbox->setPosition(wPos6 + Vec2(-100 - 22 * (i / 20), 120 - 20 * (i % 20)));
		tbox->setColor(Color3B::GREEN);
		testBox.push_back(tbox);
	}
}

void MainScene::removeTestBox()
{
	while (!testBox.empty())
	{
		for (int i = 0; i < testBox.size(); i++)
		{
			testBox[i]->removeFromParentAndCleanup(true);
			testBox[i] = nullptr;
			testBox.erase(testBox.begin() + i);
		}
	}
}

void MainScene::bulletCollision()
{
	for (int i = 0; i < Noel->BulletGroup()->size(); i++)
	{
		Rect Rct1 = Rect(
			(-bgLayer->getPositionX() + Noel->getPositionX()) + Noel->BulletGroup()->at(i)->getPositionX(),
			Noel->getPositionY() + Noel->BulletGroup()->at(i)->getPositionY() - 10,
			Noel->BulletGroup()->at(i)->getBulletBoundBox().size.width - 2,
			Noel->BulletGroup()->at(i)->getBulletBoundBox().size.height - 2
		);
		for (int j = 0; j < testBox.size(); j++)
		{
			Rect Rct2 = testBox[j]->getBoundingBox();

			if (Rct2.intersectsRect(Rct1))
			{
				Noel->RemoveBullet(i);

				testBox[j]->removeFromParentAndCleanup(true);
				testBox[j] = nullptr;
				testBox.erase(testBox.begin() + j);
			}
		}

		for (int j = 0; j < Mob.size(); j++)
		{
			if (!Mob[j]->isDead())
			{
				if (Mob[j]->getHitBox().intersectsRect(Rct1))
				{
					Noel->RemoveBullet(i);
					
					Mob[j]->setZOrder(81);
					Mob[j]->damage(1);

					if (Mob[j]->getOrder() == enemyOrder::Wait_)
						Mob[j]->order(enemyOrder::Chase_);
					
					if(Mob[j]->getHealth() <= 0)
					{
						Mob[j]->setZOrder(79);
						Mob.erase(Mob.begin() + j);
					}
					break;
				}
			}
		}
		
	}
}

void MainScene::createMob(int num)
{
	for (int i = 0; i < num; i++)
	{
		auto Aegis = EnemyCharacter::create(enemyType::Aegis);
		Aegis->setPosition(wPos4 + Vec2(random(0, 600), -180 + random(0, 370)));
		Aegis->setScale(0.9);
		Aegis->setTargetSize(Size(Noel->getHitBox().size.width, Noel->getHitBox().size.height));
		bgLayer->addChild(Aegis);

		Mob.push_back(Aegis);
		Mob[i]->setZOrder(80);
	}
}

//==========================================================
