#ifndef __Player_Animation__
#define __Player_Animation__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define MAX_ANIM 10

class PlayerAnimation : public cocos2d::Sprite
{
public:	virtual bool init();
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

	int MGInterval;
	int MGIntervaln;
	int MGStartDelay;
	int MGEndDelay;
	bool isMGRun;
	bool isMGShooting;
	bool MGPhase;
	void setMGStartDelay() { MGStartDelay = 0; isMGRun = true; };
	void setMGEndDelay() { MGEndDelay = 0; isMGShooting = false; };
	
public:

	void setAnimation(int _type);

	void runShootingCooldown();
	bool isShooting() { return isShootingCooldown; };
	int getShootingCooldown() { return ShootingCooldown; };

	void runMGStartDelay();
	void runMGEndDelay();
	bool isMGRunning() { return isMGRun; };
	bool isMGShootingRun() { return isMGShooting; };
	int getMGStartDelay() { return MGStartDelay; };
	int getMGEndDelay() { return MGEndDelay; };
	bool getMGPhase() { return MGPhase; };
	int getMGInterval() { return MGIntervaln; };
	void setMGInterval(int _interval) { MGInterval = _interval; };
	void runMGInterval();
	

	CREATE_FUNC(PlayerAnimation);
};

#endif //__Player_Animation__