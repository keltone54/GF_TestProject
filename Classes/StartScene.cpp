#include "StartScene.h"
#include "GlobalDef.h"

#include "MainScene.h"

Scene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	if (!Scene::init()) return false;

	// 레이어 ====================================================

	auto layer = Layer::create();
	this->addChild(layer);

	// 초기화 ====================================================

	initValue();
	initBackground();
	debugLabel();

	// 내용 ======================================================

	btnImage = Director::getInstance()->getTextureCache()->addImage("btn1.png");

	bt_start = Sprite::createWithTexture(btnImage);
	bt_exit = Sprite::createWithTexture(btnImage);

	bt_start->setScale(0.8);
	bt_exit->setScale(0.8);

	bt_start->setPosition(wPos2 + Vec2(0, 170));
	bt_exit->setPosition(bt_start->getPosition() + Vec2(0, -70));

	this->addChild(bt_start);
	this->addChild(bt_exit);

	TTFConfig ttfconfg("fonts/xenosphere.ttf", 32);
	auto btntxt1 = Label::createWithTTF(ttfconfg, "START");
	auto btntxt2 = Label::createWithTTF(ttfconfg, "EXIT");
	btntxt1->setPosition(bt_start->getContentSize() / 2);
	btntxt2->setPosition(bt_exit->getContentSize() / 2);
	btntxt1->setColor(Color3B(50, 50, 50));
	btntxt2->setColor(Color3B(50, 50, 50));
	bt_start->addChild(btntxt1);
	bt_exit->addChild(btntxt2);



	//============================================================

	initListener();
	return true;
}

void StartScene::initListener()
{
	this->schedule(schedule_selector(StartScene::callEveryFrame));

	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void StartScene::initValue()
{
	nSelected = 0;
	bPressed = true;
}

void StartScene::initBackground()
{
	auto bg = Sprite::create("bgstart.jpg");
	bg->setScale(0.66f);
	bg->setPosition(wPos5);
	this->addChild(bg);
}

void StartScene::debugLabel()
{
	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory, 101);
}

void StartScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

void StartScene::callEveryFrame(float f)
{
	if (bPressed)
	{
		if (nSelected == 0)
		{
			bt_start->setColor(Color3B(255, 150, 50));
			bt_exit->setColor(Color3B::WHITE);
		}
		else if (nSelected == 1)
		{
			bt_exit->setColor(Color3B(255, 150, 50));
			bt_start->setColor(Color3B::WHITE);
		}
		
		bPressed = false;
	}

	displayMemory();
}

void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_W:
	case KEY::KEY_UP_ARROW:
		if (nSelected > 0)
		{
			nSelected--;
			bPressed = true;
		}
		break;
	case KEY::KEY_S:
	case KEY::KEY_DOWN_ARROW:
		if (nSelected < 1)
		{
			nSelected++;
			bPressed = true;
		}
		break;
	case KEY::KEY_SPACE:
		if (nSelected == 0)
		{
			MoveToMainScene(this);
		}
		else if (nSelected == 1)
		{
			Director::sharedDirector()->end();
		}
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}

void StartScene::MoveToMainScene(Ref * pSender)
{
	_eventDispatcher->removeAllEventListeners();
	auto pScene = MainScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	this->removeFromParentAndCleanup(true);
}
