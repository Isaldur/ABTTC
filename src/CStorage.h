#pragma once
#include "CMap.h"
#include "CUnit.h"
#include "CBuilding.h"
#include "CScout.h"
#include "CAlly.h"
#include "functions.h"
#include "CDefenseBuilding.h"
#include "CResourceBuilding.h"
#include "CEconomyBuilding.h"
#include "CPlayer.h"
#include <memory>
#include <string>
#include <map>

using namespace std;

// this class is used to get parametres from files and stores them in its variables

class CStorage{
public:
	CStorage() = default;
	~CStorage() = default;
	
	void storeMap(int);
	void storeUnits();
	void storeBuildings();
	
	CMap createMap(istream&, int);
	map<string, shared_ptr<CUnit>> createUnits(istream&);
	map<string, shared_ptr<CBuilding>> createBuildings(istream&);
	
	map<int, shared_ptr<CBuilding>> printBuildings(bool, CPlayer&, const string& = "") const; // used in BUILD option
	void printAllUnits() const;
	void printAllBuildings();
	void addImages(istream&);

	CMap m_Map;
	map<string, shared_ptr<CUnit>>  m_Units;
	map<string, shared_ptr<CBuilding>>  m_Buildings;
};