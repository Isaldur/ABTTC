#include "CResourceBuilding.h"
#include <iostream>

using namespace std;

void CResourceBuilding::print()const {
	cout << " Name:  " << this->m_Name << endl;
	cout << " Cost:  " << this->m_Cost << endl;
	cout << " LVL:  " << this->m_Lvl << endl;
	cout << " Resource: " << this->m_Resource.m_Name << endl;
	cout << " Income:  " << this->m_Income << endl;
	cout << " BUILD on " << this->m_Resource.m_Name << "\n\n";
}

string CResourceBuilding::getResourceName()const {
	return this->m_Resource.m_Name;
}

void CResourceBuilding::updateIncome(CPlayer& player) const{
	player.m_Income += this->m_Income;
}

void CResourceBuilding::updateResources(CPlayer& player) const{
	for (size_t i = 0; i < player.m_Resources.size(); ++i) {
		if (player.m_Resources[i].m_Name == this->m_Resource.m_Name) {
			player.m_Resources[i].m_Level = this->m_Resource.m_Level;
			return;
		}
	}
	player.m_Resources.push_back(this->m_Resource);
}

int CResourceBuilding::getIncome() const{
	return this->m_Income;
}