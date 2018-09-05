#include "PopConfirm.h"
#include "GlobalDef.h"

bool PopConfirm::init()
{
	if (!Layer::init()) return false;

	//============================================================

	initValue();

	sendNoti("0", "Pause_Pop->StartScene");

	this->setOpacity(0);

	box = Sprite::create("popWin2.png");
	this->addChild(box);
	box->setPosition(wPos5);

	btnImage = Director::getInstance()->getTextureCache()->addImage("btn1.png");

	TTFConfig ttfconfg("fonts/xenosphere.ttf", 32);

	for (int i = 0; i < 2; i++)
	{
		btn[i] = Sprite::createWithTexture(btnImage);
		btn[i]->setScale(0.75);
		box->addChild(btn[i]);

		btntxt[i] = Label::createWithTTF(ttfconfg, "");
		btn[i]->addChild(btntxt[i]);
		btntxt[i]->setColor(Color3B(50, 50, 50));
		btntxt[i]->setPosition(btn[i]->getContentSize() / 2);
	}

	btn[0]->setPosition(pPos2(box) + Vec2(-100,50));
	btn[1]->setPosition(pPos2(box) + Vec2(100, 50));

	btntxt[0]->setString("CONFIRM");
	btntxt[1]->setString("CANCEL");

	btn[1]->setColor(Color3B(255, 150, 50));

	TTFConfig ttfconfg2("fonts/KBIZ-Hanmaeum-Gothic-Regular.ttf", 26);

	auto warningText = Label::createWithTTF(ttfconfg2, "저장하지 않은 데이터는 제거됩니다.\n진행하시겠습니까?");
	warningText->setPosition(pPos8(box) + Vec2(0, -16));
	warningText->setAnchorPoint(anc8);
	warningText->setAlignment(TextHAlignment::CENTER);
	warningText->setLineSpacing(5);
	box->addChild(warningText);

	//============================================================

	initListener();
	return true;
}

void PopConfirm::initListener()
{
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PopConfirm::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void PopConfirm::initValue()
{
	nSelected = 1;
	bPressed = false;
}

void PopConfirm::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_A:
	case KEY::KEY_LEFT_ARROW:
		if (nSelected > 0)
		{
			nSelected--;
			bPressed = true;
		}
		buttonSelect();
		break;
	case KEY::KEY_D:
	case KEY::KEY_RIGHT_ARROW:
		if (nSelected < 1)
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
			doConfirm(this);
			break;
		case 1:
			doClose(this);
			break;
		}
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}

void PopConfirm::buttonSelect()
{
	if (bPressed)
	{
		for (int i = 0; i < 2; i++)
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

void PopConfirm::doConfirm(Object * obj)
{
	this->removeFromParentAndCleanup(true);
	sendNoti("1", "Pause_Pop->StartScene");
}

void PopConfirm::doClose(Object * obj)
{	
	this->removeFromParentAndCleanup(true);
	sendNoti("2", "Pause_Pop->StartScene");
}
