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

	bt_start = MenuItemImage::create("Karen.png", "Karen.png");
	bt_exit = MenuItemImage::create("Tsukihi.png", "Tsukihi.png");

	bt_start->setScale(0.125f);
	bt_exit->setScale(0.125f);

	auto menu = Menu::create(bt_start, bt_exit, nullptr);
	menu->alignItemsVerticallyWithPadding(50.0f);
	menu->setPosition(wPos5 + Vec2(0, -200));
	this->addChild(menu);

	//============================================================

	{
		this->schedule(schedule_selector(StartScene::callEveryFrame));

		auto Keyboard_Listener = EventListenerKeyboard::create();
		Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	}

	//============================================================

	return true;
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
			bt_start->setOpacity(255);
			bt_exit->setOpacity(128);
			
			bt_start->setScale(0.2);
			bt_exit->setScale(0.125);
		}
		else if (nSelected == 1)
		{
			bt_exit->setOpacity(255);
			bt_start->setOpacity(128);

			bt_exit->setScale(0.2);
			bt_start->setScale(0.125);
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
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	//Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	this->removeFromParentAndCleanup(true);
}
