#ifndef __SecondScene__
#define __SecondScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

USING_NS_CC;

class SecondScene : public cocos2d::Scene
{
public: static cocos2d::Scene* createScene();
		virtual bool init();

private:

	//====================================================
	
	Layer* bgLayer;
	Layer* actLayer;

	//====================================================

	Label* lblMemory;

	//====================================================

public:

	//====================================================

	void initListener();
	void initValue();
	void initBackground();
	void debugLabel();
	void displayMemory();

	//====================================================

	void callEveryFrame(float f);

	//====================================================

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//====================================================

	void MoveToMainScene(Ref* pSender);

	//====================================================

	CREATE_FUNC(SecondScene);
};

#endif