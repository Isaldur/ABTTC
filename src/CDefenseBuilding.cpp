#include "CDefenseBuilding.h"
#include <iostream>

using namespace std;

void CDefenseBuilding::print() const{
	cout << " Name:  " << this->m_Name << endl;
	cout << " Cost:  " << this->m_Cost << endl;
	cout << " LVL:  " << this->m_Lvl << endl;
	if (this->m_Requirements.size() > 0) {
		cout << " Requirements: ";
		for (auto it = this->m_Requirements.begin(); it != this->m_Requirements.end(); ++it) {
			cout << it->m_Name << " LVL " << it->m_Level << " ";
		}
		cout << endl;
	}
	cout << " Bonus Power:  " << this->m_BonusPower << endl;
	cout << " First Strike:  " << this->m_FirstStrike << endl;
	cout << " BUILD on Field.\n\n";
}

string CDefenseBuilding::getResourceName()const {
	return " no resource";
}

void CDefenseBuilding::updateLvL(CPlayer& player)const {
	player.m_LVL = this->m_Lvl;
}