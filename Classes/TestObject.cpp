#include "TestObject.h"
#include "GlobalDef.h"

bool TestObject::init(int _type)
{
	if (!Sprite::init()) return false;
	//============================================================
	// 레이어



	//============================================================
	// 초기화
	initValue();
	debugLabel();
	//============================================================
	// 내용

	box = Sprite::create();
	box->setTextureRect(Rect(0, 0, 100, 100));
	if (_type == 0) box->setColor(Color3B::RED);
	else if (_type == 1) box->setColor(Color3B::GREEN);
	this->addChild(box);

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

	prsW = false;
	prsS = false;
	prsWS = false;
}

void TestObject::debugLabel()
{

}

void TestObject::callEveryFrame(float f)
{
	if ((prsA || prsD) && !prsAD) prsAD = true;
	else if (!prsA && !prsD && prsAD) prsAD = false;

	if ((prsW || prsS) && !prsWS) prsWS = true;
	else if (!prsW && !prsS && prsWS) prsWS = false;

	if (prsAD && prsA)
		this->setPosition(this->getPosition() + Vec2(-4, 0));
	if (prsAD && prsD)
		this->setPosition(this->getPosition() + Vec2(4, 0));

	if (prsWS && prsW)
		this->setPosition(this->getPosition() + Vec2(0, 4));
	if (prsWS && prsS)
		this->setPosition(this->getPosition() + Vec2(0, -4));
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
	case KEY::KEY_W:
		prsW = true;
		break;
	case KEY::KEY_S:
		prsS = true;
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
	case KEY::KEY_W:
		prsW = false;
		break;
	case KEY::KEY_S:
		prsS = false;
		break;
	}
}
