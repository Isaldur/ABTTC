#pragma once
#include "CBuilding.h"

class CResourceBuilding : public CBuilding{
public:
	CResourceBuilding() = default;
	CResourceBuilding(int cost, int lvl, bool isResource, int income, string name, string upgrade, CResource resource) : CBuilding(cost, lvl, isResource, move(name), move(upgrade)), m_Resource(move(resource)), m_Income(income) {}
	~CResourceBuilding() = default;

	void print() const override;
	void updateIncome(CPlayer&)const override;
	void updateResources(CPlayer&)const override;
	void updateLvL(CPlayer&)const{}
	string getResourceName()const override;
	int getIncome() const override;
	int getPower() const { return 0; }
	int getFirstStrike() const { return 0; }
	CResource getResource() const { return m_Resource; }


private:
	CResource m_Resource;
	int m_Income = 0;
};

