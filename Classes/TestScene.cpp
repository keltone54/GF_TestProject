#include "TestScene.h"
#include "GlobalDef.h"

#include "TestObject.h"
#include "EnemyCharacter.h"

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

	box = TestObject::create(1);
	this->addChild(box);
	box->setPosition(wPos5);

	auto b2 = TestObject::create(0);
	this->addChild(b2);
	b2->setPosition(wPos5 + Vec2(200, 0));

	auto z = EnemyCharacter::create(enemyType::Aegis);
	this->addChild(z);
	z->setPosition(wPos5);

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
	case KEY::KEY_SPACE:
		break;
	case KEY::KEY_GRAVE:
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}
