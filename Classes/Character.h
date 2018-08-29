#ifndef __CHARACTER__
#define __CHARACTER__

#include "cocos2d.h"

USING_NS_CC;

enum crType
{
	PLAYER,
	NPC,
	MONSTER
};

class Character
{
public:
	void init(int _type, cocos2d::Sprite* _sprite);
	void setAnimation(cocos2d::Sprite* _sprite, std::string _file, int _maxFrame, int _cols, int _rows);

};

#endif