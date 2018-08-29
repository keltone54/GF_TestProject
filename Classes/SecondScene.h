#ifndef __SecondScene__
#define __SecondScene__

#include "cocos2d.h"

class SecondScene : public cocos2d::Scene
{
public: static cocos2d::Scene* createScene();

private:

	// 변수 ==========================================================

	cocos2d::Layer* popLayer;

	//================================================================

public:
	virtual bool init();

	// 함수 ==========================================================

	void MoveToHelloWorldScene(Ref* pSender);

	//================================================================

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//================================================================

	CREATE_FUNC(SecondScene);

};

#endif