#include "Officer_Data.h"

USING_NS_CC;

void Officer_Data::SetType(__int8 _type)
{
	type = _type;
}

void Officer_Data::SetCompany(__int8 _num)
{
	company = _num;
}

void Officer_Data::SetPlatoon(__int8 _num)
{
	platoon = _num;
}

void Officer_Data::SetName(std::string _name)
{
	name.clear();
	name = _name;
}

__int8 Officer_Data::GetType()
{
	return type;
}

__int8 Officer_Data::GetCompany()
{
	return company;
}

__int8 Officer_Data::GetPlatoon()
{
	return platoon;
}

std::string Officer_Data::GetName()
{
	return name;
}
