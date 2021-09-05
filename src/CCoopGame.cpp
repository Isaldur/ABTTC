#include "CCoopGame.h"
#include "functions.h"
#include <iostream>
#include <fstream>
using namespace std;

void CCoopGame::welcome()const {
	cout << "\n Welcome great leaders. After long years at sea you finally found what you were looking for\n\n";
	cout << " New land for your empire to colonise.\n\n";
	cout << " Shortly you established a foothold from where you will explore the land.\n\n";
	cout << " Everything seems fine, but you can´t lose the feeling that you are not alone here.\n\n";
	cout << " After some time some of your men are missing and scouts recover weird looking carvings on trees\n\n";
	cout << " Your suspicion is now justified and clearly you will not have easy time colonising this land.\n\n";
	cout << " Will you and your allies use your strategical and scientific upper hand to destroy hostile clans?\n\n";
	cout << " Or will you succomb to numbers of angry locals and fall into oblivion.\n\n";
	cout << " The choice\n is yours\n\n";
}

void CCoopGame::GAMEOVER() const{
	cout << "\n Sadly you lost the war with natives. This was a grave defeat and you are forced to recall from your colonisation.\n";
	cout << "\n Not even the combined strength of multiple great minds was enough to achieve this victory.\n";
	cout << " Perhaps some day you might recover from your defeat but not any time soon.\n";

}

void CCoopGame::VICTORY() const{
	cout << "\n Congratulations! You vanquished the enemy and stabilised your foothold in this land.\n";
	cout << "\n Every one of you proved that this land and its natives are no match for your strategy and inovative knowledge.\n";
	cout << " From this day onvard you will thrive and continue colonising other lands.\n\n";
	for (size_t i = 1; i <= this->m_Players.size(); ++i) {
		int score = (m_Players[i - 1].m_Gold + (m_Players[i - 1].m_Integrity * 100)) * (this->m_Difficulty + 1);
		cout << "\n " << this->m_Players[i - 1].m_Name << " ( Player " << i << " ) score: " << score << endl;
	}
}

void CCoopGame::addDifficulty() {
	cout << " Choose game difficulty.\n";
	cout << " easy:   0\n";
	cout << " normal: 1\n";
	cout << " hard:   2\n";

	this->m_Difficulty = getchoice(0, 2);
}

void CCoopGame::savegame(){
	cout << "\n Write name of your save: ( please write different name than other saves )\n";
	string fileName;
	getline(cin, fileName);
	fileName.append(".txt");
	string path = "saves/";
	path.append(fileName);
	ofstream outFile(path);

	while (!outFile) {
		cout << "\n Write name of your save: ( please write different name than other saves )\n";
		string fileName;
		getline(cin, fileName);
		fileName.append(".txt");
		ofstream outFile(fileName);
	}
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
	output.putInt(this->m_PlayerCount);
	output.putDelimiter('\n');
	for (size_t i = 0; i < this->m_Players.size(); ++i) {
		output.putString(this->m_Players[i].m_Name);
		output.putDelimiter('\n');
		output.putInt(this->m_Players[i].m_Gold);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_ArmySize);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_Income);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_Scouts);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_LVL);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_Integrity);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_Actions);
		output.putDelimiter('\n');
		output.putBool(this->m_Players[i].lastPlayer);
		output.putDelimiter('\n');
		output.putInt(this->m_Players[i].m_Home.m_X);
		output.putDelimiter(' ');
		output.putInt(this->m_Players[i].m_Home.m_Y);
		output.putDelimiter('\n');
		for (size_t j = 0; j < this->m_Players[i].m_Resources.size(); ++j) {
			output.putDelimiter('*');
			output.putInt(this->m_Players[i].m_Resources[j].m_Level);
			output.putDelimiter('\n');
			output.putString(this->m_Players[i].m_Resources[j].m_Name);
			output.putDelimiter('\n');
		}
		for (size_t j = 0; j < this->m_Players[i].m_ScoutsAway.size(); ++j) {
			output.putDelimiter('-');
			output.putInt(this->m_Players[i].m_ScoutsAway[j].m_TimeLeft);
			output.putDelimiter(' ');
			output.putInt(this->m_Players[i].m_ScoutsAway[j].m_Scout.m_UnitSize);
			output.putDelimiter('\n');
			output.putString(this->m_Players[i].m_ScoutsAway[j].m_Scout.m_Name);
			output.putDelimiter('\n');
		}
		for (auto j = this->m_Players[i].m_Units.begin(); j != this->m_Players[i].m_Units.end(); ++j) {
			output.putDelimiter('/');
			output.putInt(j->second->m_UnitSize);
			output.putDelimiter('\n');
			output.putString(j->second->m_Name);
			output.putDelimiter('\n');
		}
	}
}

void CCoopGame::addPlayers() {
	cout << " Choose number of players (MAX 4, MIN 2)\n";

	this->m_PlayerCount = getchoice(2, 4);
	
	for (int i = 1; i <= this->m_PlayerCount; ++i) {
		cout << "\nPlayer " << i << "\n";
		this->m_Players.push_back(createPlayer(this->m_Difficulty));
		if (i == 1) {
			this->m_Players[i - 1].m_Home.m_X = 0;
			this->m_Players[i - 1].m_Home.m_Y = 0;
		}
		if (i == 2) {
			this->m_Players[i - 1].m_Home.m_X = 7;
			this->m_Players[i - 1].m_Home.m_Y = 0;
		}
		if (i == 3) {
			this->m_Players[i - 1].m_Home.m_X = 0;
			this->m_Players[i - 1].m_Home.m_Y = 7;
		}
		if (i == 4) {
			this->m_Players[i - 1].m_Home.m_X = 7;
			this->m_Players[i - 1].m_Home.m_Y = 7;
		}
	}
	m_Players[this->m_PlayerCount - 1].lastPlayer = true;
}

void CCoopGame::start() {
	if (this->loaded == false) {
		fillStorage();
	}
	cout << " The map of nearby lands: (at least what you have discovered)\n\n";
	printMap();
	shared_ptr<CGame> thisGame;
	while (true) {
		for (int i = 1; i <= this->m_PlayerCount; ++i) {
			if (this->m_BuildPhase.assault == true) {
				this->m_DefPhase.prepareEnemy(this->m_Round - 1);
				cout << "\n Settlement " << this->m_Players[i - 1].m_Name << " ! ( player " << i << " )" << endl;
				this->m_DefPhase.attack(thisGame, this->m_Players[i - 1]);
				if (this->m_Players[i - 1].gameOver == true) {
					if (this->m_Players[i - 1].lastPlayer == true && i == 1) {
						this->GAMEOVER();
						return;
					}
					else if (this->m_Players[i - 1].lastPlayer) {
						this->m_Players[i - 2].lastPlayer = true;
					}
					m_Players.erase(m_Players.begin() + i - 1); 
					--this->m_PlayerCount;
				}
				if (m_Players[i - 1].lastPlayer == true) {
					this->m_BuildPhase.assault = false;
				}
				continue;
			}
			this->m_Players[i - 1].m_Actions = 3;
			while (this->m_Players[i - 1].m_Actions > 0) {
				cout << "\n Player " << i << ":\n\n";
				thisGame = this->shared_from_this();
				
				this->m_BuildPhase.execute(thisGame, this->m_Players[i - 1]);
			}
		}
		if (this->m_Round == 5) {
			this->VICTORY();
			return;
		}
	}
}

void CCoopGame::fillStorage() {
	this->m_Storage.storeBuildings();
	this->m_Storage.storeUnits();
	this->m_Storage.storeMap(this->m_PlayerCount);
}

void CCoopGame::loadPlayers(CTokenReader& input){
	this->m_PlayerCount = input.readInt();
	input.isExpected('\n');
	CPlayer newPlayer;
	for (int i = 0; i < m_PlayerCount; ++i) {
		newPlayer.m_Name = input.readString('\n');
		newPlayer.m_Gold = input.readInt();
		input.isExpected(' ');
		newPlayer.m_ArmySize = input.readInt();
		input.isExpected(' ');
		newPlayer.m_Income = input.readInt();
		input.isExpected(' ');
		newPlayer.m_Scouts = input.readInt();
		input.isExpected(' ');
		newPlayer.m_LVL = input.readInt();
		input.isExpected(' ');
		newPlayer.m_Integrity = input.readInt();
		input.isExpected(' ');
		newPlayer.m_Actions = input.readInt();
		input.isExpected('\n');
		newPlayer.lastPlayer = input.readInt();
		input.isExpected('\n');
		newPlayer.m_Home.m_X = input.readInt();
		input.isExpected(' ');
		newPlayer.m_Home.m_Y = input.readInt();
		input.isExpected('\n');
		while (input.isExpected('*')) {
			CResource newResource;
			newResource.m_Level = input.readInt();
			input.isExpected('\n');
			newResource.m_Name = input.readString('\n');
			newPlayer.m_Resources.push_back(newResource);
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
			newPlayer.m_ScoutsAway.push_back(newScout);
		}
		while (input.isExpected('/')) {
			shared_ptr<CUnit> newUnit;
			int size = input.readInt();
			input.isExpected('\n');
			string tmp = input.readString('\n');
			shared_ptr<CUnit> storedUnit = this->m_Storage.m_Units[tmp];
			if (this->m_Storage.m_Units[tmp]->getSpeed() > 0) {
				newUnit = make_shared<CScout>(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getSpeed(), storedUnit->m_Name, storedUnit->m_Requirements);
			}
			else {
				newUnit = make_shared<CAlly>(storedUnit->m_Cost, size, storedUnit->m_LvL, storedUnit->getPower(), storedUnit->getFirstStrike(), storedUnit->getCharge(), storedUnit->m_Name, storedUnit->m_Requirements);
			}
			newPlayer.m_Units.emplace(tmp, newUnit);
		}
		this->m_Players.push_back(newPlayer);
	}
}
