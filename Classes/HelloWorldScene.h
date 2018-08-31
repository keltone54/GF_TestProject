#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "PlayerSprite.h"

USING_NS_CC;

class PlayerSprite;

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 변수 ==============================================

	Layer* actLayer;
	Layer* bgLayer;
	Label* lbl_PosX;
	Label* lbl_shootingCooldown;

	Sprite* playerBox;
	PlayerSprite setNoel;
	Sprite* sPlayer;

	Sprite* bgSprite[2];

	bool isPressedLR;
	bool isLeft;
	bool isPressLeft;
	bool isPressRight;

	bool isPressedUD;
	bool isUp;
	bool isPressUp;
	bool isPressDown;

	bool isPressSPC;

	bool isCanMove;

	// 함수 ==============================================

	void initValue();
	void debugLabel();

	void callEveryFrame(float f);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc);
	void updateLabel(cocos2d::Label* pLabel);

	void initBackground();
	void initPlayerBox();
	void initCharacter();
	void actCharacter(int _type);

	double getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni);

	//====================================================

	CREATE_FUNC(HelloWorld);
};

const short wSizeX = 1280;
const short wSizeY = 720;
const short wCenterX = wSizeX / 2;
const short wCenterY = wSizeY / 2;

#define wPos1 Vec2(0.0f, 0.0f)
#define wPos2 Vec2(wCenterX, 0.0f)
#define wPos3 Vec2(wSizeX, 0.0f)
#define wPos4 Vec2(0.0f, wCenterY)
#define wPos5 Vec2(wCenterX, wCenterY)
#define wPos6 Vec2(wSizeX, wCenterY)
#define wPos7 Vec2(0.0f, wSizeY)
#define wPos8 Vec2(wCenterX, wSizeY)
#define wPos9 Vec2(wSizeX, wSizeY)

#define anc1 Vec2(0.0f, 0.0f)
#define anc2 Vec2(0.5f, 0.0f)
#define anc3 Vec2(1.0f, 0.0f)
#define anc4 Vec2(0.0f, 0.5f)
#define anc5 Vec2(0.5f, 0.5f)
#define anc6 Vec2(1.0f, 0.5f)
#define anc7 Vec2(0.0f, 1.0f)
#define anc8 Vec2(0.5f, 1.0f)
#define anc9 Vec2(1.0f, 1.0f)

#endif // __HELLOWORLD_SCENE_H__
