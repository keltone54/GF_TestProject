#ifndef __TestScene__
#define __TestScene__

#include "cocos2d.h"

USING_NS_CC;

class TestObject;

class TestScene : public cocos2d::Scene
{
public: static Scene* createScene();
		virtual bool init();
	//====================================================

	Layer* bgLayer;
	Layer* actLayer;

	Label* lblMemory;



	//====================================================
	void initListener();
	void initValue();
	void initBackground();
	void debugLabel();
	void displayMemory();
	//====================================================
	void callEveryFrame(float f);
	//====================================================
	bool onTouchBegan(Touch* touch,	Event* event);
	//void onTouchMoved(Touch* touch,	Event* event);
	void onTouchEnded(Touch* touch,	Event* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//====================================================
	


	//====================================================
	CREATE_FUNC(TestScene);
};

#endif // __TestScene__
