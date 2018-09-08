#ifndef __EnemyCharacter__
#define __EnemyCharacter__

#include "cocos2d.h"

USING_NS_CC;

class EnemyAnimation;

class EnemyCharacter : public cocos2d::Node
{
public:	virtual bool init(int _enemyType);

private:
	int enemyType;

	Sprite* bodyBox;
	EnemyAnimation* crtAnim;

	Label* lbl_TopHead;

	bool isCanMove;

	bool isMoveBG;

	bool isPaused;

	void initCharacter();
	void initListener();
	void initValue();
	void debugLabel();

	void callEveryFrame(float f);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

public:

	//====================================================
	//void pauseAnimation();
	//void resumeAnimation();
	bool isAnimationPaused() { return isPaused; };
	//====================================================
	void showHitBox(float _opacity) { bodyBox->setOpacity(_opacity); };
	Rect getHitBox() { return Rect(this->getPosition() - bodyBox->getContentSize() / 2, bodyBox->getContentSize()); };
	//====================================================
	//bool getFlipedX();
	//====================================================

	static EnemyCharacter* EnemyCharacter::create(int _enemyType)
	{
		EnemyCharacter* obj = new (std::nothrow) EnemyCharacter;
		if (obj && obj->init(_enemyType))
		{
			obj->autorelease();
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return nullptr;
	}
};

#endif //__EnemyCharacter__