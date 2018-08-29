#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "TestData.h"

USING_NS_CC;

#define KEYCODE EventKeyboard::KeyCode


Scene* SecondScene::createScene()
{
	return SecondScene::create();
}

bool SecondScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B::WHITE);
	this->addChild(wlayer);

	//===========================================================



	// ÀÌº¥Æ® ===================================================

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(SecondScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	//===========================================================

	return true;
}

void SecondScene::MoveToHelloWorldScene(Ref* pSender)
{
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
}

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
		MoveToHelloWorldScene(this);
		break;
	case KEYCODE::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}
