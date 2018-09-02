#include "PausePopup.h"
#include "GlobalDef.h"

#include "SecondScene.h"

PausePopup::PausePopup()
{
	this->setColor(Color3B::BLACK);
	this->setAnchorPoint(anc1);

	box = Sprite::create();
	box->setTextureRect(Rect(0, 0,200, 300));
	box->setColor(Color3B::ORANGE);
	box->setPosition(wPos5);
	box->setOpacity(128.0f);
	this->addChild(box);

	sdNoel = Sprite::create("GF/sd_noel.png");
	sdNoel->setPosition(wPos4 + Vec2(300, 0));
	sdNoel->setScale(0.5f);
	this->addChild(sdNoel);
	
	{
		this->schedule(schedule_selector(PausePopup::callEveryFrame));

		auto Keyboard_Listener = EventListenerKeyboard::create();
		Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PausePopup::onKeyPressed, this);
		Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(PausePopup::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	}
}

void PausePopup::callEveryFrame(float f)
{

}

void PausePopup::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_W:
	case KEY::KEY_UP_ARROW:
		box->setPosition(box->getPosition() + Vec2(0, 50));
		break;
	case KEY::KEY_S:
	case KEY::KEY_DOWN_ARROW:
		box->setPosition(box->getPosition() + Vec2(0, -50));
		break;
	case KEY::KEY_SPACE:
		moveToSecondScene(this);
		break;
	}
}

void PausePopup::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{

}

void PausePopup::moveToSecondScene(Ref* pSender)
{
	Director::sharedDirector()->resume();

	auto pScene = SecondScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
}
