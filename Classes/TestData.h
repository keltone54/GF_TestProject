#ifndef __dataSingleton__
#define __dataSingleton__

#include "cocos2d.h"

class Soldier_Data;
class Officer_Data;

#define g_pTestData TestData::getInstance()

// 매크로 ===================================================

#define MAX_SOLDIER 128
#define MAX_COMPANY (MAX_SOLDIER / 4)
#define MAX_PLATOON (MAX_COMPANY / 4)
#define MAX_SQUAD (MAX_PLATOON / 4)

// ==========================================================

enum groupType
{
	COMPANY,
	PLATOON,
	SQUAD
};

class TestData
{
private: TestData(); static TestData* m_pInstance;
public: static TestData* getInstance();

private:

	// 변수 ==========================================================

	Soldier_Data* soldier[MAX_SOLDIER];
	Officer_Data* cOfficer[4];
	Officer_Data* pOfficer[16];
	/*Soldier_Data* soldier;
	Officer_Data* cOfficer;
	Officer_Data* pOfficer;*/

	short COMP[4][4][4][MAX_SQUAD];

	// private 함수 ==================================================

	void init_Soldiers();
	void init_Officer();

	//================================================================

public:

	// public 함수 ===================================================

	void init();
	void DeleteMemory();

	void ShowRandomSoldierProfile();

	short getSoldierNum(__int8 _c, __int8 _p, __int8 _s, __int8 _n);

	//================================================================
	
};

#endif