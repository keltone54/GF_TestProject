#ifndef __MainScene__
#define __MainScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

USING_NS_CC;

class PlayerCharacter;
class PopLayer;

class MainScene : public cocos2d::Scene
{
public: static cocos2d::Scene* createScene();
		virtual bool init();

private:

	// 변수 ==============================================

	Layer* actLayer;
	Layer* bgLayer;

	//=======================================

	Label* lblMemory;
	Label* lblPosX;
	Label* lblPosY;

	//=======================================

	PlayerCharacter* Noel;
	Sprite* bgSprite[2];

	//=======================================

	bool bPaused;

	//=======================================

public:

	// 함수 ==============================================

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

	void addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc);
	void updateLabel(cocos2d::Label* pLabel);

	double getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni);

	void moveToSecondScene(Ref* pSender);
	void moveToStartScene(Ref* pSender);

	//====================================================

	void doPop(Ref* pSender);
	void doNotification(Object* obj);
	void testAnim();

	//====================================================

	CREATE_FUNC(MainScene);
};

#endif // __MainScene_SCENE_H__
