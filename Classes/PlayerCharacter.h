#ifndef __PlayerCharacter__
#define __PlayerCharacter__

#include "cocos2d.h"

USING_NS_CC;

class PlayerAnimation;

class PlayerCharacter : public cocos2d::Node
{
private:
	Sprite* bodyBox;
	PlayerAnimation* crtAnim;
	
	Label* lbl_shootingCooldown;

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

	bool isMoveBG;

	bool isPaused;

	void initValue();
	void initCharacter();
	void debugLabel();

	void callEveryFrame(float f);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

public:	
	virtual bool init();

	//====================================================

	bool isMoveBackground();
	float getMoveBackground();
	
	void ReleaseAllKey();
	void pauseAnimation();
	void resumeAnimation();
	bool isAnimationPaused();

	CREATE_FUNC(PlayerCharacter);
};

#endif //__PlayerCharacter__