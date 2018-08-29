#ifndef __PlayerSprite__
#define __PlayerSprite__

#include "cocos2d.h"

USING_NS_CC;

enum crType
{
	PLAYER,
	NPC,
	MONSTER
};

class PlayerSprite
{
private:
	Texture2D* txWait;
	Texture2D* txMove;
	Texture2D* txAttack;
	Texture2D* txDie;
	Texture2D* txSkill;
	Texture2D* txVictory;
	Texture2D* txVictoryLoop;

	struct aniStat
	{
		Texture2D* texture;
		int maxFrame;
		int cols;
		int rows;
	};
	aniStat anime[7];


public:
	void init();
	void setAnimation(cocos2d::Sprite* _sprite, int _type);
};

#endif