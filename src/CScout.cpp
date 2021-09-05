#include "CScout.h"
#include <iostream>

using namespace std;

void CScout::print()const {
	cout << " Name: " << this->m_Name << endl;
	cout << " cost: " << this->m_Cost << endl;
	cout << " LVL: " << this->m_LvL << endl;
	if (this->m_Requirements.size() > 0) {
		cout << " Requirements: ";
		for (auto it = this->m_Requirements.begin(); it != this->m_Requirements.end(); ++it) {
			cout << it->m_Name << " LVL " << it->m_Level << " ";
		}
		cout << endl;
	}
	cout << " Speed: " << this->m_Speed << endl;
}