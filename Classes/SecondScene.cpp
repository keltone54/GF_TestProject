#include "SecondScene.h"
#include "GlobalDef.h"

#include "MainScene.h"
#include "TestData.h"

USING_NS_CC;

#define KEYCODE EventKeyboard::KeyCode

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

void SecondScene::callEveryFrame(float f)
{

}

//==========================================================

bool SecondScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return true;
}

void SecondScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void SecondScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{

}

void SecondScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case KEYCODE::KEY_TAB:
		MoveToMainScene(this);
		break;
	case KEYCODE::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}

void SecondScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	}
}

//==========================================================

void SecondScene::MoveToMainScene(Ref* pSender)
{
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
}
