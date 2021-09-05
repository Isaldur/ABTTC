#include "CPlayer.h"
#include "functions.h"
#include "CScout.h"
#include <iostream>
#include <algorithm>

using namespace std;

void CPlayer::addUnit(const shared_ptr<CUnit>& unit) {
	auto findIt = this->m_Units.find(unit->m_Name);

	if (findIt == this->m_Units.end()) {
		this->m_Units.emplace(unit->m_Name, unit);
	}
	else {
		findIt->second->m_UnitSize += unit->m_UnitSize;
	}
	this->m_ArmySize += unit->m_UnitSize;
	if (unit->m_Name == "scouts" || unit->m_Name == "striders" || unit->m_Name == "spymasters") {
		this->m_Scouts += unit->m_UnitSize;
	}
}

void CPlayer::printResources()const {
	if (this->m_Resources.empty()) {
		cout << " no resources";
	}
	else {
		for (size_t i = 0; i < m_Resources.size(); ++i) {
			cout << this->m_Resources[i].m_Name << " lvl " << this->m_Resources[i].m_Level << " ";
		}
	}
}

void CPlayer::printStats() const{
	cout << endl;
	cout << " Name: " << this->m_Name << endl;
	cout << " gold(income):  " << this->m_Gold << "(" << this->m_Income << ")\n";
	cout << " resources:  ";
	this->printResources();
	cout << endl;
	cout << " available scouts:  " << this->m_Scouts << endl;
}

CScoutAway CPlayer::sendScout(int x, int y){
	int timeAway = 0;
	if (this->m_Home.m_X == 7 && this->m_Home.m_Y == 0) {
		x = 7 - x;
	}
	if (this->m_Home.m_X == 0 && this->m_Home.m_Y == 7) {
		y = 7 - y;
	}
	if (this->m_Home.m_X == 7 && this->m_Home.m_Y == 7) {
		x = 7 - x;
		y = 7 - y;
	}

	if (x >= y) {
		timeAway = x;
	}
	else {
		timeAway = y;
	}
	
	auto it = this->m_Units.find("spymasters");
	if (it == this->m_Units.end() || it->second->m_UnitSize == 0) {
		it = this->m_Units.find("striders");
		if (it == this->m_Units.end() || it->second->m_UnitSize == 0) {
			it = this->m_Units.find("scouts");
		}
	}
	timeAway /= it->second->getSpeed();
	this->m_Units[it->first]->m_UnitSize -= 1;
	this->m_Scouts -= 1;
	this->m_ArmySize -= 1;
	CScoutAway offYouGo;
	offYouGo.m_Scout.m_Cost = it->second->m_Cost;
	offYouGo.m_Scout.m_LvL = it->second->m_LvL;
	offYouGo.m_Scout.m_Name = it->second->m_Name;
	offYouGo.m_Scout.m_Requirements = it->second->m_Requirements;
	offYouGo.m_Scout.m_Speed = it->second->getSpeed();
	offYouGo.m_TimeLeft = timeAway;
	offYouGo.m_Scout.m_UnitSize = 1;

	return offYouGo;
}

bool CPlayer::attack(CEnemyCamp& enemy, vector<CAlly>& attackSquad){
	int squadPower = 0,
		firstStrike = 0;
	for (size_t i = 0; i < attackSquad.size(); ++i) {
		squadPower += (attackSquad[i].m_Power * attackSquad[i].m_UnitSize);
		firstStrike += (attackSquad[i].m_FirstStrike * attackSquad[i].m_UnitSize);
		firstStrike += (attackSquad[i].m_ChargeBonus * attackSquad[i].m_UnitSize);
	}
	enemy.m_Power -= firstStrike;
	int result = squadPower - enemy.m_Power;
	if (result < 0) {
		enemy.m_Power -= squadPower;
		return false;
	}
	else {
		loseMen(result, attackSquad);
		this->m_Gold += enemy.m_Treasure;
		this->addUnit(enemy.m_Captives);
		return true;
	}
}

bool CPlayer::defend(vector<CAlly>& squad, int bonusPower, int bonusFirstStrike, int enemyPower){
	int squadPower = bonusPower,
		firstStrike = bonusFirstStrike;
	for (size_t i = 0; i < squad.size(); ++i) {
		squadPower += (squad[i].m_Power * squad[i].m_UnitSize);
		firstStrike += (squad[i].m_FirstStrike * squad[i].m_UnitSize);
		firstStrike += (squad[i].m_ChargeBonus * squad[i].m_UnitSize);
	}
	enemyPower -= firstStrike;
	int result = squadPower - enemyPower;
	if (result < 0) {
		return false;
	}
	else {
		loseMen(result, squad);
		return true;
	}
}

void CPlayer::loseMen(int survivors, vector<CAlly>& squad){
	sort(squad.begin(), squad.end(), compareSurvivors);
	bool first = false;
	for (size_t i = 0; i < squad.size(); ++i) {
		if (first == true) {
			squad[i].m_UnitSize = 0;
			continue;
		}
		survivors -= (squad[i].m_Power * squad[i].m_UnitSize);
		if (survivors < 0) {
			squad[i].m_UnitSize += (survivors / squad[i].m_Power);
			first = true;
		}
		this->addUnit(make_shared<CAlly>(squad[i]));
	}
}

bool CPlayer::createSquad(vector<CAlly>& squad, vector<shared_ptr<CUnit>> choiceMap){
	int choice = 0;
	for (size_t i = 0; i < choiceMap.size(); ++i) {
		cout << "\n How much " << choiceMap[i]->m_Name << " do you wish to send?\n";
		cout << " Available: " << choiceMap[i]->m_UnitSize << endl;
		cout << " Press -1 to return to menu\n";
		choice = getchoice(-1, choiceMap[i]->m_UnitSize);
		if (choice == -1) {
			return false;
		}
		else {
			squad.push_back(CAlly(choiceMap[i]->m_Cost, choice, choiceMap[i]->m_LvL, choiceMap[i]->getPower(), choiceMap[i]->getFirstStrike(), choiceMap[i]->getCharge(), choiceMap[i]->m_Name, choiceMap[i]->m_Requirements));
			this->m_Units[choiceMap[i]->m_Name]->m_UnitSize -= choice;
			this->m_ArmySize -= choice;
		}
	}
	return true;
}

void CPlayer::createDefSquad(vector<CAlly>& squad, vector<shared_ptr<CUnit>> choiceMap){
	int choice = 0;
	for (size_t i = 0; i < choiceMap.size(); ++i) {
		cout << "\n How much " << choiceMap[i]->m_Name << " do you wish to send?\n";
		cout << " Available: " << choiceMap[i]->m_UnitSize << endl;
		choice = getchoice(0, choiceMap[i]->m_UnitSize);
		if (choice == 0) {
			cout << "\n You chose not to send any of these units." << endl;
			continue;
		}
		squad.push_back(CAlly(choiceMap[i]->m_Cost, choice, choiceMap[i]->m_LvL, choiceMap[i]->getPower(), choiceMap[i]->getFirstStrike(), choiceMap[i]->getCharge(), choiceMap[i]->m_Name, choiceMap[i]->m_Requirements));
		this->m_Units[choiceMap[i]->m_Name]->m_UnitSize -= choice;
		this->m_ArmySize -= choice;
	}
}

void CPlayer::printArmy() const{
	vector<shared_ptr<CUnit>> output;

	for (auto it = this->m_Units.begin(); it != this->m_Units.end(); ++it) {
		output.push_back(it->second);
	}

	sort(output.begin(), output.end(), compareUnit);
	for (size_t i = 0; i < output.size(); ++i) {
		output[i]->print();
		cout << " Unit size: " << output[i]->m_UnitSize << endl;
		cout << endl;
	}
}



