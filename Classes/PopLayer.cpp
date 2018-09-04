#include "PopLayer.h"
#include "GlobalDef.h"

bool PopLayer::init()
{
	if (!LayerColor::init()) return false;

	//============================================================
	
	initValue();

	this->setOpacity(100.0f);

	/*auto sd_noel = Sprite::create("GF/sd_noel.png");
	sd_noel->setScale(0.5f);
	sd_noel->setPosition(wPos4 + Vec2(300, 0));
	this->addChild(sd_noel);*/

	box = Sprite::create("popWin.png");
	this->addChild(box);
	box->setScale(0.5f);
	box->setPosition(wPos5);


	btnImage = Director::getInstance()->getTextureCache()->addImage("btn1.png");
	
	TTFConfig ttfconfg("fonts/xenosphere.ttf", 32);

	for (int i = 0; i < 4; i++)
	{
		btn[i] = Sprite::createWithTexture(btnImage);
		btn[i]->setScale(1.5);
		box->addChild(btn[i]);

		btntxt[i] = Label::createWithTTF(ttfconfg, "");
		btn[i]->addChild(btntxt[i]);
		btntxt[i]->setColor(Color3B(50, 50, 50));
		btntxt[i]->setPosition(btn[i]->getContentSize() / 2);
	}

	btn[0]->setPosition(Vec2(box->getContentSize().width / 2, box->getContentSize().height - 190));
	btn[1]->setPosition(btn[0]->getPosition() + Vec2(0, -150));
	btn[2]->setPosition(btn[1]->getPosition() + Vec2(0, -150));
	btn[3]->setPosition(btn[2]->getPosition() + Vec2(0, -150));

	btntxt[0]->setString("RESUME");
	btntxt[1]->setString("RESTART");
	btntxt[2]->setString("OPTION");
	btntxt[3]->setString("EXIT");

	btn[0]->setColor(Color3B(255, 150, 50));


	//============================================================
	
	initListener();
	return true;
}

void PopLayer::initListener()
{
	auto popParam = String::create("0");
	NotificationCenter::sharedNotificationCenter()->postNotification("popup", popParam);

	this->schedule(schedule_selector(PopLayer::callEveryFrame));

	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PopLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void PopLayer::initValue()
{
	nSelected = 0;
	bPressed = false;
}

void PopLayer::callEveryFrame(float f)
{
	
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
	case KEY::KEY_W:
	case KEY::KEY_UP_ARROW:
		if (nSelected > 0)
		{
			nSelected--;
			bPressed = true;
		}
		buttonSelect();
		break;
	case KEY::KEY_S:
	case KEY::KEY_DOWN_ARROW:
		if (nSelected < 3)
		{
			nSelected++;
			bPressed = true;
		}
		buttonSelect();
		break;
	case KEY::KEY_SPACE:
		switch (nSelected)
		{
		case 0:
			doClose(this);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			doReturnStartScene(this);
			break;
		}
		break;

	case KEY::KEY_GRAVE:
		doClose(this);
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}

void PopLayer::buttonSelect()
{
	if (bPressed)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i != nSelected)
			{
				btn[i]->setColor(Color3B::WHITE);
			}
			else
			{
				btn[i]->setColor(Color3B(255, 150, 50));
			}
		}

		bPressed = false;
	}
}

void PopLayer::doClose(Object* obj)
{
	auto popParam = String::create("1");
	NotificationCenter::sharedNotificationCenter()->postNotification("popup", popParam);
	this->removeFromParentAndCleanup(true);
}

void PopLayer::doReturnStartScene(Object * obj)
{
	auto popParam = String::create("2");
	NotificationCenter::sharedNotificationCenter()->postNotification("popup", popParam);
	this->removeFromParentAndCleanup(true);
}
