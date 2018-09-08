#ifndef __Enemy_Animation__
#define __Enemy_Animation__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define MAX_ANIM 6

class EnemyAnimation : public cocos2d::Sprite
{
public:	virtual bool init(int _enemyType);
private:
	int enemyType;

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
	String enemyName;
	
	Rect hitBox;
	int health;
	float moveSpeed;
	bool ranger;

	int saveType;

	void initValue(int _enemyType);
	void addAnimInfo(std::string _name, int _maxFrame, Vec2 _anchor) { m_name.push_back(_name); m_maxFrame.push_back(_maxFrame); m_anchor.push_back(_anchor); };
	String getTypeName(int _type) { return m_name[_type]; };
	int getMaxFrame(int _type) { return m_maxFrame[_type]; };
	Vec2 getAnchor(int _type) { return m_anchor[_type]; };

public:
	void setAnimation(int _type);
	void setSaveTypeReset();
	Rect getHitBox() { return hitBox; };
	int getHealth() { return health; };
	float getMoveSpeed() { return moveSpeed; };
	bool getRanger() { return ranger; };

	static EnemyAnimation* EnemyAnimation::create(int _enemyType)
	{
		EnemyAnimation* obj = new (std::nothrow) EnemyAnimation;
		if (obj && obj->init(_enemyType))
		{
			obj->autorelease();
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return nullptr;
	}
};

#endif //__Enemy_Animation__