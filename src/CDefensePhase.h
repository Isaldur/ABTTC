#pragma once
#include "CGameptr.h"
#include "CPlayer.h"

class CDefensePhase{
public:
	CDefensePhase() = default;
	~CDefensePhase() = default;

	void prepareEnemy(int);
	void attack(CGamePtr&, CPlayer&);	// used to appoint attackers to positions on map and calculate results
	void assignAttackers(CGamePtr&, CPlayer&);

private:
	int	m_Treasure = 0,
		m_EnemyFullPower = 0,
		m_Targets = 0,
		m_EnemySmallPower = 0;
};