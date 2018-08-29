#ifndef __Soldier_Data__
#define __Soldier_Data__

#include "cocos2d.h"

enum soldierType
{
	RIFFLEMAN,
	MEDIC,
	SIGNAL
};

class Soldier_Data
{
private:
	__int8 type;
	__int8 company;
	__int8 platoon;
	__int8 squad;

	__int8 growPotentailGrade;
	__int8 growPotential;

public:
	void SetCompany(__int8 num);
	void SetPlatoon(__int8 num);
	void SetSquad(__int8 num);
	__int8 GetCompany();
	__int8 GetPlatoon();
	__int8 GetSquad();
	__int8 GetPotential();
	__int8 GetPotentialGrade();

	void SetRandomPotential();
};

#endif

