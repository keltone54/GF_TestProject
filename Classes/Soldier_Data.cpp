#include "Soldier_Data.h"

USING_NS_CC;

void Soldier_Data::SetCompany(__int8 num)
{
	company = num;
}

void Soldier_Data::SetPlatoon(__int8 num)
{
	platoon = num;
}

void Soldier_Data::SetSquad(__int8 num)
{
	squad = num;
}

__int8 Soldier_Data::GetCompany()
{
	return company;
}

__int8 Soldier_Data::GetPlatoon()
{
	return platoon;
}

__int8 Soldier_Data::GetSquad()
{
	return squad;
}

__int8 Soldier_Data::GetPotential()
{
	return growPotential;
}

__int8 Soldier_Data::GetPotentialGrade()
{
	return growPotentailGrade;
}

void Soldier_Data::SetRandomPotential()
{
	__int8 poten = cocos2d::random(1,100);
	__int8 pGrade = NULL;

	poten > 95 ? pGrade = 4 : poten > 75 ? pGrade = 3 : poten > 45 ? pGrade = 2 : pGrade = 1;

	growPotentailGrade = pGrade;

	switch (pGrade)
	{
	case 1:
		growPotential = 60 + rand() % 10;
		break;
	case 2:
		growPotential = 65 + rand() % 15;
		break;
	case 3:
		growPotential = 70 + rand() % 20;
		break;
	case 4:
		growPotential = 75 + rand() % 25;
		break;
	}
}