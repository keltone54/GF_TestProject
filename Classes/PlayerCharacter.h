#ifndef __PlayerCharacter__
#define __PlayerCharacter__

#include "cocos2d.h"

USING_NS_CC;

class PlayerAnimation;
class Bullet;

class PlayerCharacter : public cocos2d::Node
{
private:
	Sprite* bodyBox;
	PlayerAnimation* crtAnim;
	std::vector<Bullet*> bullet;
	
	Label* lbl_TopHead;
	Label* lbl_bltPos;

	bool isPressedLR;
	bool isLeft;
	bool isPressLeft;
	bool isPressRight;

	bool isPressedUD;
	bool isUp;
	bool isPressUp;
	bool isPressDown;

	bool isPressSPC;
	bool isPressShift;

	bool isCanMove;

	bool isMoveBG;

	bool isPaused;

	void initListener();
	void initValue();
	void initCharacter();
	void debugLabel();

	void callEveryFrame(float f);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

public:	
	virtual bool init();

	//====================================================
	bool isMoveBackground() { if (isMoveBG) return true; else return false; };
	float getMoveBackground();
	//====================================================
	void pauseAnimation();
	void resumeAnimation();
	bool isAnimationPaused() { return isPaused; };
	//====================================================
	void showHitBox(float _opacity) { bodyBox->setOpacity(_opacity); };
	Rect getHitBox() { return Rect(this->getPosition() - bodyBox->getContentSize() / 2, bodyBox->getContentSize()); };
	//====================================================
	bool getFlipedX();
	//====================================================
	int getShootingCoolDown();
	bool isShooting();
	//====================================================
	void BulletCreate(int _type);
	std::vector<Bullet*>* BulletGroup();
	Bullet* BulletSprite(int n);
	void RemoveBullet(int n);
	//====================================================


	CREATE_FUNC(PlayerCharacter);
};

#endif //__PlayerCharacter__