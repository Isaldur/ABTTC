#pragma once
#include "CResource.h"
#include <string>
#include <vector>

using namespace std;

class CUnit{
public:
	CUnit() = default;
	CUnit(int cost, int unitSize, int lvl, string name) : m_Cost(cost), m_UnitSize(unitSize), m_LvL(lvl), m_Name(move(name)) {}
	CUnit(int cost, int unitSize, int lvl, string name, vector<CResource> requirements) : m_Cost(cost), m_UnitSize(unitSize), m_LvL(lvl), m_Name(move(name)), m_Requirements(move(requirements)){}
	virtual ~CUnit() {};

	virtual void print()const = 0;
	virtual int getSpeed()const = 0;
	virtual int getPower()const = 0;
	virtual int getFirstStrike()const = 0;
	virtual int getCharge()const = 0;
	
	int	m_Cost = 0,
	    m_UnitSize = 0,
		m_LvL = 0;
	string m_Name;
	vector<CResource> m_Requirements;
};