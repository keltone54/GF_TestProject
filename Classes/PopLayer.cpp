#include "PopLayer.h"
#include "GlobalDef.h"

bool PopLayer::init()
{
	if (!LayerColor::init()) return false;

	//============================================================

	box = Sprite::create();
	this->addChild(box);
	box->setColor(Color3B::BLACK);
	this->setOpacity(100.0f);


	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PopLayer::onKeyPressed, this);
	Keyboard_Listener->onKeyReleased = CC_CALLBACK_2(PopLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	
	//============================================================

	return true;
}

void PopLayer::setBoxSize(float _width, float _height)
{
	box->setTextureRect(Rect(0, 0, _width, _height));
}

void PopLayer::setBoxSize(Size _size)
{
	box->setTextureRect(Rect(0, 0, _size.width, _size.height));

}

void PopLayer::setBoxSize(Vec2 _vec2)
{
	box->setTextureRect(Rect(0, 0, _vec2.x, _vec2.y));

}

void PopLayer::setBoxPosition(Vec2 _pos)
{
	box->setPosition(_pos);
}

void PopLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_SPACE:
		Director::sharedDirector()->end();
		break;
	}
}

void PopLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}
