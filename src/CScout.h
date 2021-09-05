#pragma once
#include "CUnit.h"

class CScout : public CUnit{
public:
	CScout() = default;
	CScout(int cost, int unitSize, int lvl, int speed, string name) : CUnit(cost, unitSize, lvl, name), m_Speed(speed){}
	CScout(int cost, int unitSize, int lvl, int speed, string name, vector<CResource> requirements) : CUnit(cost, unitSize, lvl, name, requirements), m_Speed(speed) {}
	
	CScout(const CScout&) = default;
	~CScout() = default;

	void print() const override;
	int getSpeed()const override { return m_Speed; }
	int getPower()const { return 0; }
	int getFirstStrike()const { return 0; }
	int getCharge()const { return 0; }
	int m_Speed = 0;	// amount of turns scout needs to show part of map and return 
};

