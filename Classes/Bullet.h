#ifndef __BULLET_MANAGER__
#define __BULLET_MANAGER__

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
public: virtual bool init();
private:
	//====================================================

	int bulletType;
	float maxRange;
	float speed;

	Texture2D* txCache;
	Texture2D* Fire_txCache;
	Sprite* Fire1;

	Rect boundBox;

	//====================================================
	void initValue();
	void setBulletBoundBox(Rect _rect);
public:
	//====================================================

	void SetBulletType(int _type) { bulletType = _type; };
	void SetBulletMaxRange(float _range) { maxRange = _range; };
	void SetBulletSpeed(float _speed) { speed = _speed; };
	void BulletCreate();
	Rect getBulletBoundBox();
	//====================================================
	CREATE_FUNC(Bullet);
};

#endif //__BULLET_MANAGER__