#include "CMainMenu.h"
#include "functions.h"
#include "CSingleGame.h"
#include "CCoopGame.h"
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void CMainMenu::printMenu() {
	cout << " Good evening Conqueror ( or whatever time of day it is ).\n\n";
	cout << " You may choose from the following options.\n\n";
	cout << " to start new SINGLEPLAYER game, press 0\n\n";
	cout << " to start new COOPERATIVE game press 1\n\n";
	cout << " if you wish to load saved game press 2\n";

	this->choice = getchoice(0, 2);
}

void CMainMenu::execute(){
	this->printMenu();
	shared_ptr<CGame> newGame;
	switch (this->choice) {
	case 0: {
		newGame = make_shared<CSingleGame>();
		break;
	}
	case 1: {
		newGame = make_shared<CCoopGame>();
		newGame->isCoop = true;
		break;
	}
	case 2: {
		this->loadGame(newGame);
		if (this->notAgain == false) {
			return;
		}
		break;
	}
	}
	if (newGame->loaded == false) {
		newGame->welcome();
		newGame->addDifficulty();
		newGame->addPlayers();
	}
	newGame->start();
	
}

void CMainMenu::loadGame(CGamePtr& newGame){
	string path = "saves";
	string output;
	size_t count = 0;
	vector<string> choices;
	for (const auto& entry : fs::directory_iterator(path)) {
		cout << " Press " << count << " to load from file: \n";
		output = entry.path().string();
		cout << output << endl;
		cout << endl;
		choices.push_back(output);
		++count;
	}
	if (count == 0) {
		cout << "\n There are no loaded saves. \n";
		return;
	}
	else {
		notAgain = true;
		cout << "\n Press -1 to return to main menu. \n";
		int choice = getchoice(-1, (int)count - 1);
		if (choice == -1) {
			notAgain = false;
			return;
		}
		string file;
		size_t pos = choices[choice].find('\\');
		if (pos != string::npos) {
			++pos;
			file = choices[choice].substr(pos);
			file.insert(0, 1, '/');
			file.insert(0, path);
		}
		else {
			file = choices[choice];
		}
		ifstream ifs;
		ifs.open(file);
		if (!ifs) {
			cout << "Unable to open file\n";
			return;
		}
		createGame(newGame, ifs);
	}
}

void CMainMenu::createGame(CGamePtr& newGame, ifstream& ifs){
	CTokenReader input(ifs);
	int gameType = input.readInt();
	if (gameType) {
		newGame = make_shared<CCoopGame>();
	}
	else {
		newGame = make_shared<CSingleGame>();
	}
	newGame->isCoop = gameType;
	newGame->m_Storage.storeBuildings();
	newGame->m_Storage.storeUnits();

	newGame->loaded = true;
	input.isExpected('\n');
	newGame->m_Storage.m_Map.m_Map = readMap(input, newGame);
	newGame->m_Turn = input.readInt();
	input.isExpected(' ');
	newGame->m_Round = input.readInt();
	input.isExpected(' ');
	newGame->m_Difficulty = input.readInt();
	input.isExpected('\n');
	newGame->loadPlayers(input);
}

vector<vector<CTile>> CMainMenu::readMap(CTokenReader& input, CGamePtr& newGame){
	vector<vector<CTile>> newMap;
	for (size_t i = 0; i <= 7; ++i) {
		vector<CTile> newLine;
		for (size_t j = 0; j <= 7; ++j) {
			CTile newTile;
			newTile.m_Discovered = input.readInt();
			input.isExpected(' ');
			newTile.m_IsEnemy = input.readInt();
			input.isExpected(' ');
			newTile.m_IsResource = input.readInt();
			input.isExpected(' ');
			newTile.m_IsBuilding = input.readInt();
			input.isExpected('\n');
			newTile.m_Integrity = input.readInt();
			input.isExpected('\n');
			newTile.m_Description = input.readString('\n');
			while (true) {
				newTile.addRow(input.readString('D'));
				if (input.isExpected('\n')) {
					break;
				}
			}
			if (newTile.m_IsEnemy) {
				newTile.m_Camp = readEnemy(input, newGame);
			}
			else if (newTile.m_IsBuilding) {
				string tmp = input.readString('\n');
				shared_ptr<CBuilding> storedBuilding = newGame->m_Storage.m_Buildings[tmp];
				newTile.m_Building = make_shared<CResourceBuilding>(storedBuilding->m_Cost, storedBuilding->m_Lvl, storedBuilding->m_isResource, storedBuilding->getIncome(), storedBuilding->m_Name, storedBuilding->m_Upgrade, storedBuilding->getResource());
			}
			newTile.m_Position.m_X = input.readInt();
			input.isExpected(' ');
			newTile.m_Position.m_Y = input.readInt();
			input.isExpected('\n');
			if (newTile.m_IsEnemy == false && newTile.m_IsResource == false) {
				for (int x = 0; x < 2; ++x) {
					for (int y = 0; y < 2; ++y) {
						newTile.m_SmallTiles[x][y] = readSmallTile(input, newGame);
					}
				}
			}
			newLine.push_back(newTile);
		}
		newMap.push_back(newLine);
	}
	return newMap;
}

CSmallTile CMainMenu::readSmallTile(CTokenReader& input, CGamePtr& newGame){
	CSmallTile newTile;
	if (input.isExpected('+')) {
		string tmp = input.readString('\n');
		shared_ptr<CBuilding> storedBuilding = newGame->m_Storage.m_Buildings[tmp];
		if(storedBuilding->getPower() > 0){
			newTile.m_Building = make_shared<CDefenseBuilding>(storedBuilding->m_Cost, storedBuilding->m_Lvl, storedBuilding->m_isResource, storedBuilding->getPower(), storedBuilding->getFirstStrike(), storedBuilding->m_Name, storedBuilding->m_Upgrade, storedBuilding->m_Requirements);
			newTile.m_Building->m_Image = storedBuilding->m_Image;
		}
		else {
			newTile.m_Building = make_shared<CEconomyBuilding>(storedBuilding->m_Cost, storedBuilding->m_Lvl, storedBuilding->m_isResource, storedBuilding->getIncome(), storedBuilding->m_Name, storedBuilding->m_Upgrade, storedBuilding->m_Requirements);
			newTile.m_Building->m_Image = storedBuilding->m_Image;
		}
	}
	else {
		newTile.makeSite();
		input.isExpected('\n');
	}
	newTile.m_Site = input.readInt();
	input.isExpected(' ');
	newTile.m_Defense = input.readInt();
	input.isExpected('\n');
	return newTile;
}

CEnemyCamp CMainMenu::readEnemy(CTokenReader& input, CGamePtr& newGame){
	CEnemyCamp newCamp;
	newCamp.m_Power = input.readInt();
	input.isExpected(' ');
	newCamp.m_Treasure = input.readInt();
	input.isExpected('\n');
	string tmp = input.readString(' '); 
	shared_ptr<CUnit> storedUnit = newGame->m_Storage.m_Units[tmp];
	int size = input.readInt();
	input.isExpected('\n');
	newCamp.m_Captives = make_shared<CAlly>(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getPower(), storedUnit->getFirstStrike(), storedUnit->getCharge(), storedUnit->m_Name, storedUnit->m_Requirements);
	
	return newCamp;
}