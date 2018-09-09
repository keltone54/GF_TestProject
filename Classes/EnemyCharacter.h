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
	EnemyAnimation* eeAnim;

	Label* lbl_TopHead;

	bool m_isDead;
	bool m_deadAction;

	Sprite* healthBar;
	Sprite* healthBarBorder;
	int health;
	int healthSave;
	int healthMax;

	Vec2 targetPos;
	Size targetSize;

	int orderType;
	bool isCanMove;
	bool isPaused;

	void initCharacter();
	void initListener();
	void initValue();
	void debugLabel();
	void setHealthBar();

	void callEveryFrame(float f);

	void deadAction();
	void deathRandomAnimation();
	void RemoveFPAC();

public:

	//====================================================
	void pauseAnimation();
	void resumeAnimation();
	bool isAnimationPaused() { return isPaused; };
	//====================================================
	void showHitBox(float _opacity) { bodyBox->setOpacity(_opacity); };
	Rect getHitBox() { return Rect(this->getPosition() - bodyBox->getContentSize() / 2, bodyBox->getContentSize()); };
	//====================================================
	bool getFlipedX();
	void setFlipedX(bool _flip);
	//====================================================
	bool isDead() { return m_isDead; };
	void order(int _order);
	int getOrder() { return orderType; };
	void damage(int _damage) { health -= _damage; };
	void setTargetPosition(Vec2 _targetPos) { targetPos = _targetPos; };
	void setTargetSize(Size _targetSize) { targetSize = _targetSize; };
	int getHealth() { return health; };
	//====================================================
	void chaseTarget();
	void marching();
	double getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni);
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