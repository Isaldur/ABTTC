#pragma once
#include "CBuilding.h"
class CDefenseBuilding : public CBuilding{
public:
	CDefenseBuilding() = default;
	~CDefenseBuilding() = default;
	CDefenseBuilding(int cost, int lvl, bool isResource, int power, int firststrike, string name, string upgrade, vector<CResource> requirements) : CBuilding(cost, lvl, isResource, move(name), move(upgrade), move(requirements)), m_BonusPower(power), m_FirstStrike(firststrike) {}

	void print()const override;
	void updateIncome(CPlayer&)const override{}
	void updateResources(CPlayer&)const override{}
	void updateLvL(CPlayer&)const;
	string getResourceName()const override;
	int getIncome() const override { return 0; }
	int getPower() const { return m_BonusPower; }
	int getFirstStrike() const { return m_FirstStrike; }
	CResource getResource() const { 
		CResource empty;
		return empty; 
	}


private:
	int m_BonusPower = 0,	// power added for defending side 
		m_FirstStrike = 0;	// number of enemy power deducted from total ( imagine something like artillery preparation ) 
};

