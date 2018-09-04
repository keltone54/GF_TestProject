#include "TestObject.h"
#include "GlobalDef.h"

bool TestObject::init()
{
	if (!Node::init()) return false;
	//============================================================
	// 레이어

	box = Sprite::create("JackO.png");
	this->addChild(box);
	
	auto karen = Sprite::create("Karen.png");
	auto tsukihi = Sprite::create("Tsukihi.png");
	box->addChild(karen);
	box->addChild(tsukihi);
	karen->setScale(0.25);
	tsukihi->setScale(0.25);
	karen->setPosition(pPos4(box));
	tsukihi->setPosition(pPos6(box));
	box->setScale(0.5);

	//============================================================
	// 초기화
	initValue();
	debugLabel();
	//============================================================
	// 내용



	//============================================================
	initListener();
	return true;
}

void TestObject::initListener()
{
	this->schedule(schedule_selector(TestObject::callEveryFrame));

	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(TestObject::onKeyPressed, this);
	Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(TestObject::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void TestObject::initValue()
{
	prsA = false;
	prsD = false;
	prsAD = false;
}

void TestObject::debugLabel()
{

}

void TestObject::callEveryFrame(float f)
{
	if ((prsA || prsD) && !prsAD) prsAD = true;
	else if (!prsA && !prsD && prsAD) prsAD = false;

	if (prsAD && prsA)
		box->setPosition(box->getPosition() + Vec2(-8, 0));
	if (prsAD && prsD)
		box->setPosition(box->getPosition() + Vec2(8, 0));
}

void TestObject::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case KEY::KEY_A:
		prsA = true;
		break;
	case KEY::KEY_D:
		prsD = true;
		break;
	}
}

void TestObject::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case KEY::KEY_A:
		prsA = false;
		break;
	case KEY::KEY_D:
		prsD = false;
		break;
	}
}
