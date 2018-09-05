#ifndef __PlayerSprite__
#define __PlayerSprite__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define MAX_ANIM 6



class PlayerAnimation : public cocos2d::Sprite
{
private:
	struct aniStat
	{
		SpriteFrameCache* texture;
		int maxFrame;
		String name;
		String file;
		Vec2 anchor;
	};
	aniStat anime[MAX_ANIM];

	vector<String>		m_name;
	vector<int>			m_maxFrame;
	vector<Vec2>		m_anchor;

	int saveType;

	void initValue();
	void addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor);
	String getTypeName(int _type);
	int getMaxFrame(int _type);
	Vec2 getAnchor(int _type);

	int ShootingCooldown;
	bool isShootingCooldown;
	void setShootingCooldown();

public:
	virtual bool init();

	void setAnimation(int _type);

	void runShootingCooldown();
	bool isShooting();
	int getShootingCooldown();

	CREATE_FUNC(PlayerAnimation);
};

#endif