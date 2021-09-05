#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ostream>
#include "CResource.h"
#include "CUnit.h"
#include "CAlly.h"
#include "CScoutAway.h"
#include "CPosition.h"
#include "CEnemyCamp.h"


using namespace std;

class CPlayer{
public:
	CPlayer() = default;
	~CPlayer() = default;

	void addUnit(const shared_ptr<CUnit>&);
	void printResources() const;
	void printStats()const;
	void printArmy()const;
	CScoutAway sendScout(int, int);
	void loseMen(int, vector<CAlly>&);
	bool createSquad(vector<CAlly>&, vector<shared_ptr<CUnit>>);
	void createDefSquad(vector<CAlly>&, vector<shared_ptr<CUnit>>);
	bool attack(CEnemyCamp&, vector<CAlly>&);
	bool defend(vector<CAlly>&, int, int, int);

	string m_Name;
	int m_Gold = 0,
		m_ArmySize = 0,
		m_Income = 0,
		m_Scouts = 0,
		m_LVL = 1,
		m_Integrity = 0,						// player lives. if you to or under 0 you lost
		m_Actions = 3;						
	bool gameOver = false;
	bool lastPlayer = false;

	CPosition m_Home;
	vector<CResource> m_Resources;
	vector<CScoutAway> m_ScoutsAway;			// Scouts currently away exploring
	map<string, shared_ptr<CUnit>>  m_Units;
};

