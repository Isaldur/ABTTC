#pragma once
#include "CBuilding.h"

class CEconomyBuilding : public CBuilding{
public:
	CEconomyBuilding(int cost, int lvl, bool isResource, int income, string name, string upgrade, vector<CResource> requirements) : CBuilding(cost, lvl, isResource, move(name), move(upgrade), move(requirements)), m_Income(income) {}
	~CEconomyBuilding() = default;

	void print()const override;
	void updateIncome(CPlayer&)const override;
	void updateResources(CPlayer&)const override {}
	void updateLvL(CPlayer&)const{}
	string getResourceName()const override;
	int getIncome() const override;
	int getPower() const { return 0; }
	int getFirstStrike() const { return 0; }
	CResource getResource() const {
		CResource empty;
		return empty;
	}


private:
	int m_Income = 0;		// income by turn
};

