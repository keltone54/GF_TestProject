#include "TestScene.h"
#include "GlobalDef.h"

#include "TestObject.h"

Scene* TestScene::createScene()
{
	return TestScene::create();
}

bool TestScene::init()
{
	if (!Scene::init()) return false;
	//============================================================
	// 레이어

	bgLayer = Layer::create();
	actLayer1 = Layer::create();
	actLayer2 = Layer::create();
	this->addChild(bgLayer);
	this->addChild(actLayer1);
	this->addChild(actLayer2);

	//============================================================
	// 초기화
	initValue();
	initBackground();
	debugLabel();
	//============================================================
	// 내용

	auto z = Sprite::create();
	z->setTextureRect(Rect(0, 0, 50, 50));
	z->setColor(Color3B::WHITE);
	z->setPosition(wPos4 + Vec2(200, 0));
	actLayer1->addChild(z);

	auto ac = MoveBy::create(0.5, Vec2(100, 0));
	auto ac2 = ac->reverse();
	auto seq = Sequence::create(ac, ac2, nullptr);
	auto rep = RepeatForever::create(seq);
	z->runAction(rep);

	box = TestObject::create();
	box->setPosition(wPos5);
	this->addChild(box);

	//============================================================
	initListener();
	return true;
}

void TestScene::initListener()
{
	this->schedule(schedule_selector(TestScene::callEveryFrame));
	
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void TestScene::initValue()
{
	bPuz = false;
}

void TestScene::initBackground()
{
	auto bg = Sprite::create("bgstart.jpg");
	bg->setScale(0.66f);
	bg->setPosition(wPos5);
	bgLayer->addChild(bg);
}

void TestScene::debugLabel()
{
	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory, 101);
}

void TestScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

void TestScene::callEveryFrame(float f)
{

	displayMemory();

}

void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_1:
	{
		auto z = Sprite::create();
		z->setTextureRect(Rect(0, 0, 20, 20));
		z->setColor(Color3B::WHITE);
		z->setPosition(wPos8 + Vec2(0, -100));
		actLayer2->addChild(z);
		z->setTag(99);

		auto ac = MoveBy::create(5, Vec2(400, 0));
		z->runAction(ac);
	}
		break;
	case KEY::KEY_GRAVE:
		if (!bPuz)
		{
			box->pause();
			box->getEventDispatcher()->resumeEventListenersForTarget(box, true);
		}
		else
		{
			box->resume();
		}
		bPuz ? bPuz = false : bPuz = true;
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}
