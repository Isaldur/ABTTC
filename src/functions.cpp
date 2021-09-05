#include "functions.h"
#include <limits>

using namespace std;

int getchoice(int low, int high) {
	int choice = 0;
	while (!(cin >> choice) || choice < low || choice > high) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "please, enter valid " << low << " to " << high << " number\n";
	}
	/*if (choice < low || choice > high) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = 0;
		cout << "please, enter valid " << low << " to " << high << " number\n";
		getchoice(low, high);
	}*/
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return choice;
}

CPlayer createPlayer(int difficulty) {
	CPlayer newplayer;
	cout << "\nEnter the name of your colony:\n";
	getline(cin >> ws, newplayer.m_Name);
	switch (difficulty) {
		case 0: {
			newplayer.m_Gold = 300;
			newplayer.m_Income = 200;
			newplayer.m_Integrity = 20;
			newplayer.addUnit(make_shared<CScout>(100, 3, 1, 1, "scouts"));
			newplayer.addUnit(make_shared<CAlly>(1, 500, 1, 1, 0, 0, "spearmen"));
			break;
		}
		case 1: {
			newplayer.m_Gold = 200;
			newplayer.m_Income = 150;
			newplayer.m_Integrity = 15;
			newplayer.addUnit(make_shared<CScout>(100, 2, 1, 1, "scouts"));
			newplayer.addUnit(make_shared<CAlly>(1, 250, 1, 1, 0, 0, "spearmen"));
			break;
		}
		case 2: {
			newplayer.m_Gold = 100;
			newplayer.m_Income = 100;
			newplayer.m_Integrity = 10;
			newplayer.addUnit(make_shared<CScout>(100, 1, 1, 1, "scouts"));
			newplayer.addUnit(make_shared<CAlly>(1, 100, 1, 1, 0, 0, "spearmen"));
			break;
		}
	}
	newplayer.m_LVL = 1;

	cout << "\n Colony " << newplayer.m_Name << " has:\n\n";
	cout << " LVL " << newplayer.m_LVL << endl;
	cout << " " << newplayer.m_Gold << "  Gold\n";
	cout << " " << newplayer.m_Income << "  Base income\n";
	cout << " " << newplayer.m_ArmySize << "  Army size\n";
	cout << " " << newplayer.m_Scouts << "  Scouts\n\n";

	return newplayer;
}

void insertUnit(shared_ptr<CUnit> unit, map<string, shared_ptr<CUnit>>& units) {
	units.insert(make_pair(unit->m_Name, move(unit)));
}

void insertBuilding(shared_ptr<CBuilding> building, map<string, shared_ptr<CBuilding>>& buildings) {
	buildings.insert(make_pair(building->m_Name, move(building)));
}

bool haveRequirements(const vector<CResource>& playerRes, const vector<CResource>& neededRes) {
	size_t countSame = 0;
	for (size_t i = 0; i < neededRes.size(); ++i) {
		for (size_t j = 0; j < playerRes.size(); ++j) {
			if (playerRes[j] >= neededRes[i]) {
				++countSame;
				break;
			}
		}
	}
	if (countSame >= neededRes.size()) {
		return true;
	}
	
	return false;
}

bool compareBuilding(const shared_ptr<CBuilding>& x, const shared_ptr<CBuilding>& y) {
	if (x->m_Lvl == y->m_Lvl) {
		return x->m_Name < y->m_Name;
	}
	else {
		return x->m_Lvl < y->m_Lvl;
	}
}

bool compareUnit(const shared_ptr<CUnit>& x, const shared_ptr<CUnit>& y){
	if (x->m_LvL == y->m_LvL) {
		return x->m_Cost < y->m_Cost;
	}
	else {
		return x->m_LvL < y->m_LvL;
	}
}

bool compareSurvivors(const CAlly& x, const CAlly& y) {
	if (x.m_FirstStrike == y.m_FirstStrike) {
		if (x.m_ChargeBonus == y.m_ChargeBonus) {
			return x.m_LvL > y.m_LvL;
		}
		else {
			return x.m_ChargeBonus > y.m_ChargeBonus;
		}
	}
	else {
		return x.m_FirstStrike > y.m_FirstStrike;
	}
}