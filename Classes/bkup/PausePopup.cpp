#include "PausePopup.h"
#include "GlobalDef.h"

#include "SecondScene.h"
#include "PlayerCharacter.h"

PausePopup::PausePopup()
{
	m_pCharacter = nullptr;
}

bool PausePopup::init()
{
	if (!LayerColor::init()) return false;

	this->setColor(Color3B::BLACK);
	this->setAnchorPoint(anc1);

	initMenuBox();

	/*sdNoel = Sprite::create("GF/sd_noel.png");
	sdNoel->setPosition(wPos4 + Vec2(300, 0));
	sdNoel->setScale(0.5f);
	this->addChild(sdNoel);*/

	{
		this->schedule(schedule_selector(PausePopup::callEveryFrame));

		/*auto Keyboard_Listener = EventListenerKeyboard::create();
		Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PausePopup::onKeyPressed, this);
		Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(PausePopup::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);*/
	}

	return true;
}

void PausePopup::initMenuBox()
{
	box = Sprite::create();
	box->setTextureRect(Rect(0, 0, 160, 180));
	box->setColor(Color3B::BLACK);
	box->setPosition(wPos5 + Vec2(0, 160));
	box->setOpacity(50.0f);
	this->addChild(box);

	auto btn1 = MenuItemImage::create("btn1-1.png", "btn1-2.png", CC_CALLBACK_1(PausePopup::menuResume, this));
	auto btn2 = MenuItemImage::create("btn2-1.png", "btn2-2.png", CC_CALLBACK_1(PausePopup::menuVoid, this));
	auto btn3 = MenuItemImage::create("btn3-1.png", "btn3-2.png", CC_CALLBACK_1(PausePopup::menuSceneMove, this));

	auto menu = Menu::create(btn1, btn2, btn3, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(box->getContentSize() / 2);
	box->addChild(menu);
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
		break;
	}
}

void PausePopup::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{

}


//======================================================

void PausePopup::moveToSecondScene(Ref* pSender)
{
	Director::sharedDirector()->resume();

	auto pScene = SecondScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, pScene));
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(0.5f, pScene));
}

void PausePopup::setPopupPause(PlayerCharacter* _Character)
{
	m_pCharacter = _Character;
}

void PausePopup::menuResume(Ref* pSender)
{
	this->setVisible(false);
	this->setOpacity(0.0);
	m_pCharacter->resumeAnimation();

	this->pause();
	Director::sharedDirector()->resume();	
}

void PausePopup::menuSceneMove(Ref* pSender)
{
	moveToSecondScene(this);
}

void PausePopup::menuVoid(Ref* pSender)
{

}