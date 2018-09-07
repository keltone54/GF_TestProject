#ifndef __PlayerSprite__
#define __PlayerSprite__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define MAX_ANIM 10

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
	void addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor) { m_name.push_back(_name); m_maxFrame.push_back(_maxFrame); m_anchor.push_back(_anchor); };
	String getTypeName(int _type) { return m_name[_type]; };
	int getMaxFrame(int _type) { return m_maxFrame[_type]; };
	Vec2 getAnchor(int _type) { return m_anchor[_type]; };

	int ShootingCooldown;
	bool isShootingCooldown;
	void setShootingCooldown() { ShootingCooldown = 0; isShootingCooldown = true; };

	int MGStartDelay;
	int MGEndDelay;
	bool isMGRun;
	bool isMGShooting;
	void setMGStartDelay() { MGStartDelay = 0; isMGRun = true; log("setMGStartDelay"); };
	void setMGEndDelay() { MGEndDelay = 0; isMGShooting = false; };
	
public:
	virtual bool init();

	void setAnimation(int _type);

	void runShootingCooldown();
	bool isShooting() { return isShootingCooldown; };
	int getShootingCooldown() { return ShootingCooldown; };

	void runMGStartDelay();
	void runMGEndDelay();
	bool isMGRunning() { return isMGRun; };
	int getMGStartDelay() { return MGStartDelay; };
	int getMGEndDelay() { return MGEndDelay; };
	bool isMGShootingRun() { return isMGShooting; };
	

	CREATE_FUNC(PlayerAnimation);
};

#endif