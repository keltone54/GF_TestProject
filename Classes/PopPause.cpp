#include "PopPause.h"
#include "GlobalDef.h"

#include "PopConfirm.h"

bool PopPause::init()
{
	if (!LayerColor::init()) return false;

	//============================================================
	
	initValue();

	sendNoti("0", "popup");

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
	createNoti(PopPause,"Pause_Pop->StartScene", notiAction, this);
	initListener();
	return true;
}

void PopPause::initListener()
{
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(PopPause::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void PopPause::initValue()
{
	nSelected = 0;
	bPressed = false;
}

void PopPause::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
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
			doConfirmPop(this);
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

void PopPause::buttonSelect()
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

void PopPause::doClose(Object* obj)
{
	deleteAllNoti(this);
	this->removeFromParentAndCleanup(true);
	sendNoti("1", "popup");
}

void PopPause::doReturnStartScene(Object * obj)
{
	deleteAllNoti(this);
	this->removeFromParentAndCleanup(true);
	sendNoti("2", "popup");
}

void PopPause::doConfirmPop(Ref* pSender)
{
	auto pPop = PopConfirm::create();
	this->addChild(pPop);
}

void PopPause::notiAction(Object * obj)
{
	auto pParam = (String*)obj;

	if (pParam->intValue() == 0) // Create
	{
		this->getEventDispatcher()->pauseEventListenersForTarget(this, true);
	}
	else if (pParam->intValue() == 1) // Confirm to StartScene
	{
		doReturnStartScene(this);
	}
	else if (pParam->intValue() == 2) // Cancel to StartScene
	{
		CallFuncDelay();
	}
}

void PopPause::resumeDispatcher()
{
	this->getEventDispatcher()->resumeEventListenersForTarget(this, true);
}

void PopPause::CallFuncDelay()
{
	auto seq = Sequence::create(DelayTime::create(0.01), CallFunc::create(CC_CALLBACK_0(PopPause::resumeDispatcher, this)), nullptr);
	this->runAction(seq);
}
