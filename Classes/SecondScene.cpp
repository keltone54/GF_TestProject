#include "SecondScene.h"
#include "GlobalDef.h"

#include "MainScene.h"


Scene* SecondScene::createScene()
{
	return SecondScene::create();
}

bool SecondScene::init()
{
	if (!Scene::init()) return false;

	// 레이어 ====================================================

	bgLayer = Layer::create();
	this->addChild(bgLayer);
	actLayer = Layer::create();
	this->addChild(actLayer);

	// 내용 ======================================================

	initValue();
	initBackground();
	debugLabel();

	//============================================================

	{
		this->schedule(schedule_selector(SecondScene::callEveryFrame));

		auto Keyboard_Listener = EventListenerKeyboard::create();
		Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(SecondScene::onKeyPressed, this);
		Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(SecondScene::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	}

	//============================================================

	return true;
}

//==========================================================

void SecondScene::initValue()
{

}

void SecondScene::initBackground()
{
	auto bgSprite = Sprite::create("GF/Forest.jpg");

	bgSprite->setPosition(wPos5);
	bgSprite->setScale(1.25f, 1.0f);

	bgLayer->addChild(bgSprite);
}

void SecondScene::debugLabel()
{
	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory);
}

void SecondScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

void SecondScene::callEveryFrame(float f)
{
	
	displayMemory();

}

//==========================================================

bool SecondScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void SecondScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void SecondScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void SecondScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case KEY::KEY_TAB:
		MoveToMainScene(this);
		break;
	case KEY::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}

void SecondScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{

	}
}

//==========================================================

void SecondScene::MoveToMainScene(Ref* pSender)
{
	_eventDispatcher->removeAllEventListeners();
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	//Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
	//this->removeFromParentAndCleanup(true);
}
