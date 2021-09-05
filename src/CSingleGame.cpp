#include "CSingleGame.h"
#include "functions.h"
#include "CBuildPhaseMenu.h"
#include <fstream>
#include <iostream>

using namespace std;

void CSingleGame::welcome()const {
	cout << "\n Welcome great leader. After long years at sea you finally found what you were looking for\n\n";
	cout << " New land for your empire to colonise.\n\n";
	cout << " Shortly you established a foothold from where you will explore the land.\n\n";
	cout << " Everything seems fine, but you can´t lose the feeling that you are not alone here.\n\n";
	cout << " After some time some of your men are missing and scouts recover weird looking carvings on trees\n\n";
	cout << " Your suspicion is now justified and clearly you will not have easy time colonising this land.\n\n";
	cout << " Will you use your strategical and scientific upper hand to destroy hostile clans?\n\n";
	cout << " Or will you succomb to numbers of angry locals and fall into oblivion.\n\n";
	cout << " The choice\n is yours\n\n";
}

void CSingleGame::addDifficulty() {
	cout << " Choose game difficulty:\n\n";
	cout << " easy:   0\n";
	cout << " normal: 1\n";
	cout << " hard:   2\n";

	this->m_Difficulty = getchoice(0, 2);
}

void CSingleGame::addPlayers() {
	this->m_Player = createPlayer(this->m_Difficulty);
	this->m_Player.lastPlayer = true;
	this->m_Player.m_Home.m_X = 0;
	this->m_Player.m_Home.m_Y = 0;
}

void CSingleGame::start() {
	if (this->loaded == false) {
		fillStorage();
	}
	cout << " The map of nearby lands: (at least what you have discovered)\n\n";
	printMap();
	shared_ptr<CGame> thisGame;
	while (true) {
		if (this->m_Player.m_Actions == 0 && this->m_BuildPhase.endedTurn == false) {
			cout << "\n You have 0 actions left. Ending turn.\n\n";
			this->m_BuildPhase.endTurn(thisGame, this->m_Player);
			this->m_Player.m_Actions = 3;
		}
		if (this->m_Player.m_Actions == 0) {
			this->m_Player.m_Actions = 3;
		}
		thisGame = this->shared_from_this();
		if (this->m_BuildPhase.assault == true) {
			this->m_DefPhase.prepareEnemy(this->m_Round - 1);
			this->m_DefPhase.attack(thisGame, this->m_Player);
			if (this->m_Player.gameOver == true) {
				this->GAMEOVER();
				return;
			}
			else if(this->m_Round == 5){
				this->VICTORY();
				return;
			}
			this->m_BuildPhase.assault = false;
		}
		this->m_BuildPhase.execute(thisGame, this->m_Player);
	}
}

void CSingleGame::fillStorage() {
	this->m_Storage.storeBuildings();
	this->m_Storage.storeUnits();
	this->m_Storage.storeMap(1);
}

void CSingleGame::loadPlayers(CTokenReader& input){
	this->m_Player.m_Name = input.readString('\n');
	this->m_Player.m_Gold = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_ArmySize = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_Income = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_Scouts = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_LVL = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_Integrity = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_Actions = input.readInt();
	input.isExpected('\n');
	this->m_Player.lastPlayer = input.readInt();
	input.isExpected('\n');
	this->m_Player.m_Home.m_X = input.readInt();
	input.isExpected(' ');
	this->m_Player.m_Home.m_Y = input.readInt();
	input.isExpected('\n');
	while (input.isExpected('*')) {
		CResource newResource;
		newResource.m_Level = input.readInt();
		input.isExpected('\n');
		newResource.m_Name = input.readString('\n');
		this->m_Player.m_Resources.push_back(newResource);
	}
	while (input.isExpected('-')) {
		CScoutAway newScout;
		newScout.m_TimeLeft = input.readInt();
		input.isExpected(' ');
		int size = input.readInt();
		input.isExpected('\n');
		string tmp = input.readString('\n');
		shared_ptr<CUnit> storedUnit = this->m_Storage.m_Units[tmp];
		newScout.m_Scout = CScout(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getSpeed(), storedUnit->m_Name, storedUnit->m_Requirements);
		this->m_Player.m_ScoutsAway.push_back(newScout);
	}
	while (input.isExpected('/')) {
		shared_ptr<CUnit> newUnit;
		int size = input.readInt();
		input.isExpected('\n');
		string tmp = input.readString('\n');
		shared_ptr<CUnit> storedUnit = this->m_Storage.m_Units[tmp];;
		if (this->m_Storage.m_Units[tmp]->getSpeed() > 0) {
			newUnit = make_shared<CScout>(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getSpeed(), storedUnit->m_Name, storedUnit->m_Requirements);
		}
		else {
			newUnit = make_shared<CAlly>(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getPower(), storedUnit->getFirstStrike(), storedUnit->getCharge(), storedUnit->m_Name, storedUnit->m_Requirements);
		}
		this->m_Player.m_Units.emplace(tmp, newUnit);
	}
}

void CSingleGame::VICTORY() const{
	cout << "\n Congratulations! You vanquished the enemy and stabilised your foothold in this land.\n";
	cout << " From this day onvard you will thrive and continue colonising other lands.\n\n";
	int score = (m_Player.m_Gold + (m_Player.m_Integrity * 100)) * (this->m_Difficulty + 1);
	cout << "\n " << this->m_Player.m_Name << " score: " << score << endl;
}

void CSingleGame::GAMEOVER() const{
	cout << "\n Sadly you lost the war with natives. This was a grave defeat and you are forced to recall from your colonisation.\n";
	cout << " Perhaps some day you might recover from your defeat but not any time soon.\n";
}

void CSingleGame::savegame(){
	cout << "\n Write name of your save: ( writing same name as previous save is going to overwrite it )\n";
	string fileName;
	getline(cin, fileName);
	fileName.append(".txt");
	string path = "saves/";
	path.append(fileName);
	ofstream outFile(path);

	CTokenPutter output(outFile);
	output.putBool(this->isCoop);
	output.putDelimiter('\n');
	saveMap(m_Storage.m_Map.m_Map, output);
	output.putInt(this->m_Turn);
	output.putDelimiter(' ');
	output.putInt(this->m_Round);
	output.putDelimiter(' ');
	output.putInt(this->m_Difficulty);
	output.putDelimiter('\n');
	output.putString(m_Player.m_Name);
	output.putDelimiter('\n');
	output.putInt(m_Player.m_Gold);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_ArmySize);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_Income);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_Scouts);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_LVL);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_Integrity);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_Actions);
	output.putDelimiter('\n');
	output.putBool(m_Player.lastPlayer);
	output.putDelimiter('\n');
	output.putInt(m_Player.m_Home.m_X);
	output.putDelimiter(' ');
	output.putInt(m_Player.m_Home.m_Y);
	output.putDelimiter('\n');
	for (size_t j = 0; j < m_Player.m_Resources.size(); ++j) {
		output.putDelimiter('*');
		output.putInt(m_Player.m_Resources[j].m_Level);
		output.putDelimiter('\n');
		output.putString(m_Player.m_Resources[j].m_Name);
		output.putDelimiter('\n');
	}
	for (size_t j = 0; j < m_Player.m_ScoutsAway.size(); ++j) {
		output.putDelimiter('-');
		output.putInt(m_Player.m_ScoutsAway[j].m_TimeLeft);
		output.putDelimiter(' ');
		output.putInt(m_Player.m_ScoutsAway[j].m_Scout.m_UnitSize);
		output.putDelimiter('\n');
		output.putString(m_Player.m_ScoutsAway[j].m_Scout.m_Name);
		output.putDelimiter('\n');
	}
	for (auto j = m_Player.m_Units.begin(); j != m_Player.m_Units.end(); ++j) {
		output.putDelimiter('/');
		output.putInt(j->second->m_UnitSize);
		output.putDelimiter('\n');
		output.putString(j->second->m_Name);
		output.putDelimiter('\n');
	}
}

