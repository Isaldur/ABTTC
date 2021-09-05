#pragma once
#include "CUnit.h"
#include "CResource.h"
#include <vector>
#include <string>
// this class represents a unit trained and used to defend by the player

class CAlly : public CUnit{
public:
	CAlly(int cost, int unitSize, int lvl, int power, int firststrike, int charge, string name) : CUnit(cost, unitSize, lvl, name), m_Power(power), m_FirstStrike(firststrike), m_ChargeBonus(charge) {}
	CAlly(int cost, int unitSize, int lvl, int power, int firststrike, int charge, string name, vector<CResource> requirements) : CUnit(cost, unitSize, lvl, name, requirements), m_Power(power), m_FirstStrike(firststrike), m_ChargeBonus(charge) {}
	~CAlly() = default;

	void print() const override;
	int getSpeed()const override{ return 0; }
	int getPower()const { return m_Power; }
	int getFirstStrike()const { return m_FirstStrike; }
	int getCharge()const { return m_ChargeBonus; }

	int m_Power = 0,
		m_FirstStrike = 0,	// deducts enemy power before fight
		m_ChargeBonus = 0;	// works same as firststrike but is mostly bigger number and harder to get ( cavalry is more expensive than archers )
};