#ifndef __TestScene__
#define __TestScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

USING_NS_CC;

class TestObject;

class TestScene : public cocos2d::Scene
{
public: static Scene* createScene();
		virtual bool init();
private:
	//====================================================

	Layer* bgLayer;
	Layer* actLayer1;
	Layer* actLayer2;

	Label* lblMemory;

	TestObject* box;

	bool bPuz;

	//====================================================
	void initListener();
	void initValue();
	void initBackground();
	void debugLabel();
	void displayMemory();
	void callEveryFrame(float f);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
public:
	//====================================================



	//====================================================
	CREATE_FUNC(TestScene);
};

#endif // __TestScene__
