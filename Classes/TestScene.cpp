#include "TestScene.h"
#include "GlobalDef.h"

#include "TestObject.h"
#include "PlayerCharacter.h"

Scene* TestScene::createScene()
{
	return TestScene::create();
}

bool TestScene::init()
{
	if (!Scene::init()) return false;
	//============================================================
	// 레이어

	bgLayer = Layer::create();
	actLayer1 = Layer::create();
	actLayer2 = Layer::create();
	this->addChild(bgLayer);
	this->addChild(actLayer1);
	this->addChild(actLayer2);

	//============================================================
	// 초기화
	initValue();
	initBackground();
	debugLabel();
	//============================================================
	// 내용

	bltcache = Director::getInstance()->getTextureCache()->addImage("GF/Bullet/bullet_HG.png");

	Noel = PlayerCharacter::create();
	actLayer1->addChild(Noel);
	Noel->setPosition(wPos5);
	Noel->showHitBox(255);

	//============================================================
	initListener();
	return true;
}

void TestScene::initListener()
{
	this->schedule(schedule_selector(TestScene::callEveryFrame));
	
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
}

void TestScene::initValue()
{
	
}

void TestScene::initBackground()
{
	auto bg = Sprite::create("bgstart.jpg");
	bg->setScale(0.66f);
	bg->setPosition(wPos5);
	bgLayer->addChild(bg);
}

void TestScene::debugLabel()
{
	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory, 101);

	lbl1 = Label::create("", "", 24);
	lbl1->setPosition(wPos7 + Vec2(20, -20));
	lbl1->setAnchorPoint(anc7);
	lbl1->setColor(Color3B::WHITE);
	this->addChild(lbl1);

	lbl2 = Label::create("", "", 24);
	lbl2->setPosition(lbl1->getPosition() + Vec2(0, -30));
	lbl2->setAnchorPoint(anc7);
	lbl2->setColor(Color3B::WHITE);
	this->addChild(lbl2);

	lbl3 = Label::create("", "", 24);
	lbl3->setPosition(lbl2->getPosition() + Vec2(0, -30));
	lbl3->setAnchorPoint(anc7);
	lbl3->setColor(Color3B::WHITE);
	this->addChild(lbl3);

	lbl4 = Label::create("", "", 24);
	lbl4->setPosition(lbl3->getPosition() + Vec2(0, -30));
	lbl4->setAnchorPoint(anc7);
	lbl4->setColor(Color3B::WHITE);
	this->addChild(lbl4);
}

void TestScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

void TestScene::callEveryFrame(float f)
{
	displayMemory();

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->getBoundingBox().intersectsRect(Noel->getHitBox()) || !v[i]->isVisible())
		{
			v[i]->removeFromParentAndCleanup(true);
			v[i] = nullptr;
			v.erase(v.begin() + i);
		}
	}

	lbl1->setString(StringUtils::format("v Size : %d",v.size()));
	//lbl2->setString(StringUtils::format(""));
	//lbl3->setString(StringUtils::format(""));
	//lbl4->setString(StringUtils::format(""));
	
}

void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_SPACE:
		createBullet();
		break;
	case KEY::KEY_GRAVE:
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}

void TestScene::createBullet()
{
	auto blt = Sprite::createWithTexture(bltcache);
	actLayer1->addChild(blt);
	blt->setOpacity(0);
	v.push_back(blt);

	if (Noel->getFlipedX())
	{
		auto seq = Sequence::create(
			DelayTime::create(0.1),
			FadeTo::create(0, 255),
			MoveBy::create(1, Vec2(-wSizeX, 0)),
			Hide::create(), nullptr);
		blt->setFlippedX(true);
		blt->runAction(seq);
		blt->setPosition(Noel->getPosition() + Vec2(-50, 8));
	}
	else
	{
		auto seq = Sequence::create(
			DelayTime::create(0.1),
			FadeTo::create(0, 255),
			MoveBy::create(1, Vec2(wSizeX, 0)),
			Hide::create(), nullptr);
		blt->setFlippedX(false);
		blt->runAction(seq);
		blt->setPosition(Noel->getPosition() + Vec2(50, 8));
	}
}
