#include "CBuildPhaseMenu.h"
#include "functions.h"
#include "CGAME.h"
#include <iostream>
using namespace std;

void CBuildPhaseMenu::printMenu(CGamePtr& thisGame, CPlayer& player) {
	
	cout << " Turn: " << thisGame->m_Turn << " Round: " << thisGame->m_Round << " Build phase\n";
	player.printStats();
	cout << "\n Available actions: (actions left: " << player.m_Actions << ")\n\n";

	cout << "                1. BUILD / UPGRADE\n\n";
	cout << "                2. TRAIN (choo choo)\n\n";
	cout << "                3. EXPLORE\n\n";
	cout << "                4. ATTACK\n\n";
	cout << "                5. SHOW MAP ( does not cost actions )\n\n";
	cout << "                6. SHOW PLAYER STATS ( does not cost actions )\n\n";
	cout << "                7. END TURN\n\n";
	cout << "                8. SAVE AND QUIT GAME\n\n";

	this->choice = getchoice(1, 8);
}

void CBuildPhaseMenu::printUnitMenu(CGamePtr& thisGame, CPlayer& player) {
	int count = 0;
	vector<shared_ptr<CUnit>> choices;
	cout << "\n Available units:\n\n";
	for (auto it = thisGame->m_Storage.m_Units.begin(); it != thisGame->m_Storage.m_Units.end(); ++it) {
		if (player.m_LVL >= it->second->m_LvL && haveRequirements(player.m_Resources, it->second->m_Requirements)) {
			cout << "\n Press " << count << " to train this unit:\n";
			it->second->print();
			choices.push_back(it->second);
			++count;
		}
	}
	if (count == 0) {
		cout << "\n No available units need more gold\n\n";
		return;
	}
	cout << " Press -1 to return\n";
	this->choice = getchoice(-1, (int)choices.size() - 1);
	if (choice == -1) {
		return;
	}
	shared_ptr<CUnit> newUnit = choices[this->choice];
	cout << "\n You have chosen " << newUnit->m_Name << endl;

	int max = player.m_Gold / newUnit->m_Cost;
	cout << "\n You can afford " << max << "  " << newUnit->m_Name << endl;
	cout << "\n How many do you want to train? ( choose number from 0 to " << max << " ) \n";
	cout << " Press -1 to return\n";
	int newRecruits = getchoice(-1, max);
	if (newRecruits == -1) {
		return;
	}
	cout << "\n You have recruited " << newRecruits << " " << newUnit->m_Name << endl;

	newUnit->m_UnitSize = newRecruits;
	player.addUnit(newUnit);
	player.m_Gold -= (newRecruits * newUnit->m_Cost);
	--player.m_Actions;
}

void CBuildPhaseMenu::printAttackMenu(CGamePtr& thisGame, CPlayer& player, CTile& chosen){
	cout << "\n Choose units to attack with.\n\n";
	vector<shared_ptr<CUnit>> choices;
	for (auto it = player.m_Units.begin(); it != player.m_Units.end(); ++it) {
		if (it->second->getSpeed() != 0 || it->second->m_UnitSize == 0) {
			continue;
		}
		cout << "\n Press 0 to attack with this unit:\n";
		it->second->print();
		cout << " Press 1 to skip this unit\n";
		cout << " Press -1 to return to menu\n";
		choice = getchoice(-1, 1);
		if (choice == -1) {
			return;
		}
		else if (choice == 0) {
			choices.push_back(it->second);
		}
		else {
			continue;
		}
		cout << endl;
	}
	if (choices.size() == 0) {
		cout << "\n\n You cannot or choose not to send any troops. Returning to menu.\n\n";
		return;
	}
	vector<CAlly> attackSquad;
	if (player.createSquad(attackSquad, choices) == false) {
		return;
	}
	if (player.attack(chosen.m_Camp, attackSquad) == false) {
		cout << "\n You have lost this battle, but the enemy lost as much as you did. Return later with bigger army.\n\n";
	}
	else {
		cout << "\n You have achieved victory!\n\n";
		cout << " In the camp you managed to find treasure worth " << chosen.m_Camp.m_Treasure << " gold.\n";
		cout << " Also, you found some of your lost men: \n\n";
		chosen.m_Camp.m_Captives->print();
		cout << "\n Unit size: " << chosen.m_Camp.m_Captives->m_UnitSize << endl;

		chosen.m_IsEnemy = false;
		chosen.m_Camp.m_Captives = nullptr;
		chosen.m_Camp.m_Treasure = 0;
		chosen.m_Camp.m_Power = 0;
		chosen.m_Description = "field";
		chosen.m_Tile.clear();
		chosen.addRow("     Field     ");
		chosen.addRow(" ----------*-- ");
		chosen.addRow(" ---*------|-- ");
		chosen.addRow(" ------------- ");
		chosen.addRow(" ------------- ");
		chosen.m_SmallTiles[0][0].m_Building = thisGame->m_Storage.m_Buildings["small tower"];
		chosen.m_SmallTiles[0][1].makeSite();
		chosen.m_SmallTiles[1][0].makeSite();
		chosen.m_SmallTiles[1][1].makeSite();
		--player.m_Actions;
	}
}

void CBuildPhaseMenu::execute(CGamePtr& thisGame, CPlayer& player) {
	this->endedTurn = false;
	this->printMenu(thisGame, player);
	switch (this->choice) {
	case 1: {
		build(thisGame, player);
		break;
	}
	case 2: {
		train(thisGame, player);
		break;
	}
	case 3: {
		explore(thisGame, player);
		break;
	}
	case 4: {
		attack(thisGame, player);
		break;
	}
	case 5: {
		showMap(thisGame);
		break;
	}
	case 6: {
		showStats(player);
		break;
	}
	case 7: {
		endTurn(thisGame, player);
		break;
	}
	case 8: {
		thisGame->savegame();
		exit(0);
		break;
	}
	}
}

void CBuildPhaseMenu::build(CGamePtr& thisGame, CPlayer& player) {
	thisGame->printBuildings();
	thisGame->printMap();

	cout << "\n\n Choose X coordinate to BUILD on ( you can only build on FIELDS or on already settled places )\n";
	cout << " Press -1 to return\n";
	int x = getchoice(-1, 7);
	if (x == -1) {
		return;
	}
	cout << "\n\n Choose Y coordinate to BUILD on ( you can only build on FIELDS or on already settled places )\n";
	cout << " Press -1 to return\n";
	int y = getchoice(-1, 7);
	if (y == -1) {
		return;
	}
	CTile& chosen = thisGame->m_Storage.m_Map.m_Map[x][y];
	if (chosen.m_Discovered == false) {
		cout << "\n This tile is not yet discovered\n\n";
		return;
	}
	if (chosen.m_Description != "field" && !chosen.m_IsEnemy && chosen.m_Description != "Starting position") {
		if (chosen.m_IsBuilding) {
			shared_ptr<CBuilding> upgrade = this->buildMenu.upgradeMenu(thisGame, player, chosen.m_Building);
			if (upgrade) {
				chosen.m_Building = upgrade;
				cout << "\n You have UPGRADED building to " << upgrade->m_Name << endl;
				--player.m_Actions;
			}
		}
		else {
			shared_ptr<CBuilding> newBuilding = this->buildMenu.printResourceMenu(thisGame, player, chosen.m_Description);
			if (newBuilding) {
				chosen.m_Building = newBuilding;
				chosen.m_IsBuilding = true;
				cout << "\n You have built a " << chosen.m_Building->m_Name << endl;
				--player.m_Actions;
			}
		}
		return;
	}
	if (chosen.m_Description != "field" && chosen.m_Description != "Starting position") {
		cout << "\n\n Choose a discovered field or settlement!\n";
		return;
	}
	else {
		chosen.printZoom();
		cout << "\n\n Choose X coordinate to build on\n";
		cout << " Press -1 to return\n";
		int smallX = getchoice(-1, 1);
		if (smallX == -1) {
			return;
		}
		cout << "\n\n Choose y coordinate to build on\n";
		cout << " Press -1 to return\n";
		int smallY = getchoice(-1, 1);
		if (smallY == -1) {
			return;
		}
		CSmallTile& chosen = thisGame->m_Storage.m_Map.m_Map[x][y].m_SmallTiles[smallX][smallY];
		if (chosen.m_Site == true) {
			shared_ptr<CBuilding> newBuilding = this->buildMenu.printMenu(thisGame, player);
			if (newBuilding) {
				chosen.m_Building = newBuilding;
				chosen.m_Site = false;
				cout << "\n You have built a " << chosen.m_Building->m_Name << endl;
				if (chosen.m_Building->getPower() > 0) {
					chosen.m_Defense = true;
				}
				--player.m_Actions;
				return;
			}
		}
		else {
			shared_ptr<CBuilding> upgrade = this->buildMenu.upgradeMenu(thisGame, player, chosen.m_Building);
			if (upgrade) {
				chosen.m_Building = upgrade;
				cout << "\n You have UPGRADED building to " << upgrade->m_Name << endl;
				--player.m_Actions;
			}
		}
	}
}

void CBuildPhaseMenu::train(CGamePtr& thisGame, CPlayer& player) {
	thisGame->printUnits();
	printUnitMenu(thisGame, player);
}

void CBuildPhaseMenu::explore(CGamePtr& thisGame, CPlayer& player){
	if (player.m_Scouts == 0) {
		cout << "\n You have no scouts available." << endl;
	}
	else {
		thisGame->printMap();
		cout << "\n\n Choose X coordinate to EXPLORE ( you can only EXPLORE undiscovered tiles that are next to discovered tiles. )\n";
		cout << " Press -1 to return\n";
		int x = getchoice(-1, 7);
		if (x == -1) {
			return;
		}
		cout << "\n\n Choose Y coordinate to EXPLORE ( you can only EXPLORE undiscovered tiles that are next to discovered tiles. )\n";
		int y = getchoice(-1, 7);
		if (y == -1) {
			return;
		}
		if (thisGame->m_Storage.m_Map.m_Map[x][y].canExplore(thisGame) == false) {
			cout << "\n Choose tile next to discovered tile.\n\n";
		}
		else {
			thisGame->m_Storage.m_Map.m_Map[x][y].m_Discovered = true;
			cout << "\n You have discovered a new part of country.\n\n";
			player.m_ScoutsAway.push_back(player.sendScout(x, y));
			--player.m_Actions;
		}
	}
}

void CBuildPhaseMenu::attack(CGamePtr& thisGame, CPlayer& player) {
	thisGame->printMap();
	cout << "\n\n Choose X coordinate to attack enemy camp. \n";
	cout << " Press -1 to return\n";
	int x = getchoice(-1, 7);
	if (x == -1) {
		return;
	}
	cout << "\n\n Choose Y coordinate to attack enemy camp. \n";
	cout << " Press -1 to return\n";
	int y = getchoice(-1, 7);
	if (y == -1) {
		return;
	}
	CTile& chosen = thisGame->m_Storage.m_Map.m_Map[x][y];
	if (chosen.m_Discovered == false || chosen.m_IsEnemy == false) {
		cout << "\n\n Choose a discovered Enemy camp!\n";
	}
	else {
		cout << "\n This camp has power of " << chosen.m_Camp.m_Power << endl;
		printAttackMenu(thisGame, player, chosen);
	}
}

void CBuildPhaseMenu::showMap(CGamePtr& thisGame) {
	thisGame->printMap();
	cout << "\n\n If you want to go back press -1.\n";
	cout << "\n If you want to zoom to a tile press 0.\n\n";
	this->choice = getchoice(-1, 0);

	switch (choice) {
	case -1: {
		break;
	}
	case 0: {
		cout << "\n\n Choose X coordinate to SHOW tile. \n";
		cout << " Press -1 to return\n";
		int x = getchoice(-1, 7);
		if (x == -1) {
			return;
		}
		cout << "\n\n Choose Y coordinate to SHOW tile. \n";
		cout << " Press -1 to return\n";
		int y = getchoice(-1, 7);
		if (y == -1) {
			return;
		}
		CTile& chosen = thisGame->m_Storage.m_Map.m_Map[x][y];
		if (chosen.m_Discovered == false) {
			cout << "\n Choose discovered tile.\n";
			return;
		}
		if (chosen.m_IsResource) {
			chosen.printResourceTile();
			return;
		}
		if (chosen.m_IsEnemy) {
			chosen.printEnemyTile();
			return;
		}
		if (chosen.m_Description != "field" && chosen.m_Description != "Starting position") {
			cout << "\n Can only zoom to field or settlement.\n";
		}
		else {
			chosen.printZoom();
		}
		break;
	}
	}
}

void CBuildPhaseMenu::showStats(CPlayer& player){
	player.printStats();
	cout << endl;
	cout << "\n Army size: " << player.m_ArmySize;
	cout << "\n Your army: \n\n";
	player.printArmy();
}

void CBuildPhaseMenu::endTurn(CGamePtr& thisGame, CPlayer& player){
	player.m_Actions = 0;
	if (player.lastPlayer == true) {
		this->endedTurn = true;
		++thisGame->m_Turn;
		if (thisGame->m_Turn == 11) {
			thisGame->m_Turn = 1;
			++thisGame->m_Round;
			this->assault = true;
		}
	}
	player.m_Gold += player.m_Income;
	for (size_t i = 0; i < player.m_ScoutsAway.size(); ++i) {
		--player.m_ScoutsAway[i].m_TimeLeft;
		if (player.m_ScoutsAway[i].m_TimeLeft <= 0) {
			player.addUnit(make_shared<CScout>(player.m_ScoutsAway[i].m_Scout));
			player.m_ScoutsAway.erase(player.m_ScoutsAway.begin() + i);
		}
	}
}

