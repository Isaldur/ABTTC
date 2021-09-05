#include "CDefensePhase.h"
#include "CGAME.h"
#include "CTile.h"

void CDefensePhase::prepareEnemy(int count){
	this->m_EnemyFullPower = 5000 * count;
	this->m_Treasure = 500 * count;
}

void CDefensePhase::attack(CGamePtr& thisGame, CPlayer& player){
	cout << "\n\n You are under ATTACK!\n";
	cout << " Enemy has total power of: " << this->m_EnemyFullPower << endl;
	cout << " And if you manage to survive you will get their treasure worth " << this->m_Treasure << " gold.\n";
	cout << "\n Enemy will attack your main base and up to 3 more settled fields next to it." << endl;
	cout << "\n You will be informed by your scouts the enemy army sizes that attack individual fields." << endl;
	cout << "\n According to that, you should be able to assign units to defend as much as possible." << endl;
	assignAttackers(thisGame, player);
}

void CDefensePhase::assignAttackers(CGamePtr& thisGame, CPlayer& player){
	int x = player.m_Home.m_X,
		y = player.m_Home.m_Y;
	vector<vector<CTile>> thisMap = thisGame->m_Storage.m_Map.m_Map;
	CTile attackZone[2][2];
	if (x == 0 && y == 0) {
		attackZone[0][0] = thisMap[x][y];
		attackZone[1][0] = thisMap[x + 1][y];
		attackZone[0][1] = thisMap[x][y + 1];
		attackZone[1][1] = thisMap[x + 1][y + 1];
	}
	else if (x == 0 && y == 7) {
		attackZone[0][0] = thisMap[x][y - 1];
		attackZone[1][0] = thisMap[x + 1][y - 1];
		attackZone[0][1] = thisMap[x][y];
		attackZone[1][1] = thisMap[x + 1][y];
	}
	else if (x == 7 && y == 0) {
		attackZone[0][0] = thisMap[x - 1][y];
		attackZone[1][0] = thisMap[x][y];
		attackZone[0][1] = thisMap[x - 1][y + 1];
		attackZone[1][1] = thisMap[x][y + 1];
	}
	else if (x == 7 && y == 7) {
		attackZone[0][0] = thisMap[x - 1][y - 1];
		attackZone[1][0] = thisMap[x][y - 1];
		attackZone[0][1] = thisMap[x - 1][y];
		attackZone[1][1] = thisMap[x][y];
	}
	this->m_Targets = 4;
	this->m_EnemySmallPower = this->m_EnemyFullPower / this->m_Targets;

	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {

			CTile quarter = attackZone[i][j];
			int bonusPower = 0,
				bonusFirstStrike = 0;
			cout << "\n There is " << this->m_EnemySmallPower << " enemies going to attack this tile: \n\n";
			if (quarter.m_IsResource == true) {
				quarter.printResourceTile();
			}
			else {
				quarter.printZoom();
			}
			for (size_t x = 0; x < 2; ++x) {
				for (size_t y = 0; y < 2; ++y) {
					CSmallTile defBuilding = quarter.m_SmallTiles[x][y];
					if (defBuilding.m_Defense == true) {
						cout << "\n This building can help with defeating the enemies: \n";
						defBuilding.m_Building->print();
						bonusPower += defBuilding.m_Building->getPower();
						bonusFirstStrike += defBuilding.m_Building->getFirstStrike();
					}
				}
			}

			int choice = 0;
			vector<shared_ptr<CUnit>> choiceMap;
			for (auto it = player.m_Units.begin(); it != player.m_Units.end(); ++it) {
				if (it->second->getSpeed() != 0 || it->second->m_UnitSize == 0) {
					continue;
				}
				cout << "\n Press 0 to defend with this unit:\n";
				it->second->print();
				cout << " Press 1 to skip this unit\n";
				choice = getchoice(0, 1);
				if (choice == 0) {
					choiceMap.push_back(it->second);
				}
				else {
					continue;
				}
				cout << endl;
			}
			vector<CAlly> defenseSquad;
			player.createDefSquad(defenseSquad, choiceMap);
			if (player.defend(defenseSquad, bonusPower, bonusFirstStrike, this->m_EnemySmallPower) == false) {
				cout << "\n You lost this battle, but war with the natives is far from over.\n";
				player.m_Integrity -= quarter.m_Integrity;
				cout << "\n Due to enemy victory your integrity crumbles. ( you lost " << quarter.m_Integrity << " ) you have " << player.m_Integrity << " left.\n\n";
				if (player.m_Integrity <= 0) {
					player.gameOver = true;
					return;
				}
			}
			else {
				cout << "\n Well done Conqueror! You managed to defeat the enemy and defend this part of country.\n";
			}
		}
	}
	cout << "\n Thanks to the sacrifice of your brave men, your colony survived. But bevare.\n";
	cout << " The enemy will learn from this defeat and send much larger force to destroy your precious settlement.\n";
	cout << " You found treasure worth " << this->m_Treasure << " gold in the enemy camp. Use it well.\n\n";
	player.m_Gold += this->m_Treasure;
}
