#ifndef __StartScene__
#define __StartScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public cocos2d::Scene
{
public: static cocos2d::Scene* createScene();
		virtual bool init();

private:

	//====================================================

	MenuItemImage* bt_start;
	MenuItemImage* bt_exit;

	int nSelected;
	bool bPressed;

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

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//====================================================

	void MoveToMainScene(Ref* pSender);

	//====================================================

	CREATE_FUNC(StartScene);
};

#endif //__StartScene__