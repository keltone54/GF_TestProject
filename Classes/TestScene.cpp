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
	actLayer = Layer::create();
	this->addChild(bgLayer);
	this->addChild(actLayer);

	//============================================================
	// 초기화
	initValue();
	initBackground();
	debugLabel();
	//============================================================
	// 내용

	

	//============================================================
	initListener();
	return true;
}

void TestScene::initListener()
{
	this->schedule(schedule_selector(TestScene::callEveryFrame));
	
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	
	auto Touch_Listener = EventListenerTouchOneByOne::create();
	Touch_Listener->setSwallowTouches(true);
	Touch_Listener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchBegan, this);
	Touch_Listener->onTouchEnded = CC_CALLBACK_2(TestScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Touch_Listener, this);
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

//=========================================================================

void TestScene::callEveryFrame(float f)
{
	displayMemory();
}

//=========================================================================

bool TestScene::onTouchBegan(Touch* touch, Event* event)
{
	auto tp = touch->getLocation();
	
	return true;
}

void TestScene::onTouchEnded(Touch* touch, Event* event)
{

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

