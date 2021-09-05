#include "CEconomyBuilding.h"
#include <iostream>

using namespace std;

void CEconomyBuilding::print() const {
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
	cout << " Income:  " << this->m_Income << endl;
	cout << " BUILD on Field.\n\n";
}

string CEconomyBuilding::getResourceName()const {
	return " no resource";
}

void CEconomyBuilding::updateIncome(CPlayer& player) const{
	player.m_Income += this->m_Income;
}

int CEconomyBuilding::getIncome() const{
	return this->m_Income;
}
