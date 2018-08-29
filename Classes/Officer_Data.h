#ifndef __Officer_Data__
#define __Officer_Data__

#include "cocos2d.h"

enum officerType
{
	COMPANY_COMMANDER,
	PLATOON_COMMANDER
};

class Officer_Data
{
private:
	__int8 type;
	__int8 company;
	__int8 platoon;
	std::string name;

public:

	void SetType(__int8 _type);
	void SetCompany(__int8 _num);
	void SetPlatoon(__int8 _num);
	void SetName(std::string _name);

	__int8 GetType();
	__int8 GetCompany();
	__int8 GetPlatoon();
	std::string GetName();

};

#endif
