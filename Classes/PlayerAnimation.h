#ifndef __PlayerSprite__
#define __PlayerSprite__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define MAX_ANIM 6

enum actList
{
	Wait,
	Move,
	Attack,
	Die,
	Victory,
	VictoryLoop
};

class PlayerAnimation : public cocos2d::Sprite
{
private:
	struct aniStat
	{
		SpriteFrameCache* texture;
		int maxFrame;
		std::string name;
		std::string file;
		Vec2 anchor;
	};
	aniStat anime[MAX_ANIM];

	vector<std::string> m_name;
	vector<int>			m_maxFrame;
	vector<Vec2>		m_anchor;

	void initValue();
	void addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor);
	std::string getTypeName(int _type);
	int getMaxFrame(int _type);
	Vec2 getAnchor(int _type);

	int ShootingCooldown;
	bool isShootingCooldown;
	void setShootingCooldown();

public:
	PlayerAnimation();

	void setAnimation(int _type);

	void runShootingCooldown();
	bool isShooting();
	int getShootingCooldown();

	CREATE_FUNC(PlayerAnimation);
};

#endif