#include "TestData.h"
#include "Soldier_Data.h"
#include "Officer_Data.h"

USING_NS_CC;

TestData* TestData::m_pInstance = NULL;

TestData* TestData::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new TestData;
	}

	return m_pInstance;
}

TestData::TestData()
{

}

void TestData::init()
{
	init_Soldiers();
	init_Officer();
	log("g_pTestData init complete");
}

void TestData::DeleteMemory()
{
	for (int i = 0; i < MAX_SOLDIER; i++) delete soldier[i];
	for (int i = 0; i < 4; i++) delete cOfficer[i];
	for (int i = 0; i < 16; i++) delete pOfficer[i];
}

void TestData::ShowRandomSoldierProfile()
{
	for (int i = 0; i < MAX_SOLDIER; i++)
	{
		log("no.%d\tCompany:%d  Platoon:%d  Squad:%d  Potential:%d  Grade:%d",
			i + 1,
			(int)soldier[i]->GetCompany(),
			(int)soldier[i]->GetPlatoon(),
			(int)soldier[i]->GetSquad(),
			(int)soldier[i]->GetPotential(),
			(int)soldier[i]->GetPotentialGrade());
	}
}

short TestData::getSoldierNum(__int8 _c, __int8 _p, __int8 _s, __int8 _n)
{
	return COMP[(int)_c][(int)_p][(int)_s][(int)_n];
}

void TestData::init_Soldiers()
{
	short n = 0;
	short n2 = 0;

	for (short i = 0; i < MAX_SOLDIER; i++)
	{
		soldier[i] = new Soldier_Data;

		__int8 c = NULL;

		{
			i < MAX_COMPANY ? c = 1 : i < MAX_COMPANY * 2 ? c = 2 : i < MAX_COMPANY * 3 ? c = 3 : c = 4;
			soldier[i]->SetCompany(c);
			n < MAX_PLATOON ? soldier[i]->SetPlatoon(1) : n < MAX_PLATOON * 2 ? soldier[i]->SetPlatoon(2) : n < MAX_PLATOON * 3 ? soldier[i]->SetPlatoon(3) : soldier[i]->SetPlatoon(4);
			n2 < MAX_SQUAD ? soldier[i]->SetSquad(1) : n2 < MAX_SQUAD * 2 ? soldier[i]->SetSquad(2) : n2 < MAX_SQUAD * 3 ? soldier[i]->SetSquad(3) : soldier[i]->SetSquad(4);
		}

		soldier[i]->SetRandomPotential();

		if (n + 1 >= MAX_COMPANY)
		{
			n = 0;
		}
		else n++;

		if (n2 + 1 >= MAX_PLATOON)
		{
			n2 = 0;
		}
		else n2++;

		if (i + 1 == MAX_SOLDIER)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int z = 0; z < 4; z++)
				{
					for (int x = 0; x < 4; x++)
					{
						for (int q = 0; q < MAX_SQUAD; q++)
						{
							COMP[j][z][x][q] = q + (x * MAX_SQUAD + (z * MAX_PLATOON + (j * MAX_COMPANY)));
						}
					}
				}
			}
		}
	}
}

void TestData::init_Officer()
{
	std::string cOfficerName[4] = {
		"1st_Rommel",
		"2nd_Guderian",
		"3rd_Manstein",
		"4th_Degurechaff" };

	std::string pOfficerName[16] = {
		"1-1","1-2","1-3","1-4",
		"2-1","2-2","2-3","2-4",
		"3-1","3-2","3-3","3-4",
		"4-1","4-2","4-3","4-4" };

	for (__int8 i = 0; i < 4; i++) // cOfficer init
	{
		cOfficer[i] = new Officer_Data;

		cOfficer[i]->SetType(officerType::COMPANY_COMMANDER);
		cOfficer[i]->SetCompany(i);
		cOfficer[i]->SetPlatoon(0);
		//pOfficer[i]->SetName(cOfficerName[i]);
	}

	__int8 n = 0;
	__int8 n2 = 0;

	for (__int8 i = 0; i < 16; i++) // pOfficer init
	{
		pOfficer[i] = new Officer_Data;

		pOfficer[i]->SetType(officerType::PLATOON_COMMANDER);
		pOfficer[i]->SetCompany(n);
		pOfficer[i]->SetPlatoon(n2);
		//pOfficer[i]->SetName(pOfficerName[i]);

		if ((i + 1) / 4 == 0) n++;

		n2++;
		if (n2 >= 4) n2 = 0;
	}
}

