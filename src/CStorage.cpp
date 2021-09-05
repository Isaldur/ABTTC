#include "CStorage.h"
#include "CTokenReader.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

static const char minusD = '-';
static const char comma = ',';
static const char star = '*';
static const char newLine = '\n';
static const char slash = '/';

CMap CStorage::createMap(istream& mapDef, int playerCount) {
	CMap newMap;
	CTokenReader input(mapDef);
	
	newMap.m_Map.resize(8);
	for (int i = 0; i <= 7; ++i) {
		newMap.m_Map[i].resize(8);
	}

	while (input && !input.eof()) {
		string tileName = input.readString(minusD);
		while (true) {
			int x = input.readInt();
			input.readDelimiter(slash);
			int y = input.readInt();
			newMap.createTile(x, y, tileName, playerCount);
			if (input.isExpectedOrEof(newLine)) {
				break;
			}
			input.readDelimiter(comma);
		}
	}
	return newMap;
}

map<string, shared_ptr<CUnit>> CStorage::createUnits(istream& unitsDef) {
	map<string, shared_ptr<CUnit>> newUnits;
	CTokenReader input(unitsDef);
	
	while (input && !input.eof()) {
		if (input.isExpected(slash)) {
			break;
		}
		string unitName = input.readString(minusD);
		int cost = input.readInt();
		input.readDelimiter(comma);
		int lvl = input.readInt();
		input.readDelimiter(comma);
		int speed = input.readInt();
		vector<CResource> requirements;

		while (input.isExpected(star)) {
			CResource requirement;
			requirement.m_Name = input.readString(comma);
			requirement.m_Level = input.readInt();
			requirements.push_back(requirement);
		}

		if (!input.isExpectedOrEof(newLine)) {
			unitsDef.setstate(ios_base::failbit);
			break;
		}
		insertUnit(make_shared<CScout>(cost, 0, lvl, speed, unitName, requirements), newUnits);
	}
	
	while (input && !input.eof()) {
		string unitName = input.readString(minusD);
		int cost = input.readInt();
		input.readDelimiter(comma);
		int lvl = input.readInt();
		input.readDelimiter(comma);
		int power = input.readInt();
		input.readDelimiter(comma);
		int firstStrike = input.readInt();
		input.readDelimiter(comma);
		int charge = input.readInt();
		vector<CResource> requirements;

		while (input.isExpected(star)) {
			CResource requirement;
			requirement.m_Name = input.readString(comma);
			requirement.m_Level = input.readInt();
			requirements.push_back(requirement);
		}

		if (!input.isExpectedOrEof(newLine)) {
			unitsDef.setstate(ios_base::failbit);
			break;
		}
		insertUnit(make_shared<CAlly>(cost, 0, lvl, power, firstStrike, charge, unitName, requirements), newUnits);
	}
	return newUnits;
}
map<string, shared_ptr<CBuilding>> CStorage::createBuildings(istream& buildingsDef) {
	map<string, shared_ptr<CBuilding>> newBuildings;
	CTokenReader input(buildingsDef);
	
	while (input && !input.eof()) {
		if (input.isExpected(slash)) {
			break;
		}
		string buildingName = input.readString(minusD);
		int cost = input.readInt();
		input.readDelimiter(comma);
		int lvl = input.readInt();
		input.readDelimiter(comma);
		int defense = input.readInt();
		input.readDelimiter(comma);
		int firstStrike = input.readInt();
		vector<CResource> requirements;

		while (input.isExpected(star)) {
			CResource requirement;
			requirement.m_Name = input.readString(comma);
			requirement.m_Level = input.readInt();
			requirements.push_back(requirement);
		}
		string upgrade;
		if (input.isExpected(minusD)) {
			upgrade = input.readString(newLine);
		}
		else {
			upgrade = "";
			if (!input.isExpectedOrEof(newLine)) {
				buildingsDef.setstate(ios_base::failbit);
				break;
			}
		}

		insertBuilding(make_shared<CDefenseBuilding>(cost, lvl, false, defense, firstStrike, buildingName, upgrade, requirements), newBuildings);
	}

	while (input && !input.eof()) {
		if (input.isExpected(slash)) {
			break;
		}
		string buildingName = input.readString(minusD);
		int cost = input.readInt();
		input.readDelimiter(comma);
		int lvl = input.readInt();
		input.readDelimiter(comma);
		int income = input.readInt();
		vector<CResource> requirements;

		while (input.isExpected(star)) {
			CResource requirement;
			requirement.m_Name = input.readString(comma);
			requirement.m_Level = input.readInt();
			requirements.push_back(requirement);
		}
		string upgrade;
		if (input.isExpected(minusD)) {
			upgrade = input.readString(newLine);
		}
		else {
			upgrade = "";
			if (!input.isExpectedOrEof(newLine)) {
				buildingsDef.setstate(ios_base::failbit);
				break;
			}
		}
		insertBuilding(make_shared<CEconomyBuilding>(cost, lvl, false, income, buildingName, upgrade, requirements), newBuildings);
	}

	CResource newResource;
	while (input && !input.eof()) {
		string buildingName = input.readString(minusD);
		int cost = input.readInt();
		input.readDelimiter(comma);
		newResource.m_Level = input.readInt();
		input.readDelimiter(comma);
		int income = input.readInt();
		input.readDelimiter(comma);
		newResource.m_Name = input.readString(comma);
		string upgrade = input.readString(newLine);
		
		if (input.isExpectedOrEof(newLine)) {
			buildingsDef.setstate(ios_base::failbit);
			break;
		}

		insertBuilding(make_shared<CResourceBuilding>(cost, newResource.m_Level, true, income, buildingName, upgrade, newResource), newBuildings);
	}

	return newBuildings;
}

void CStorage::storeMap(int playerCount) {
	ifstream inFile;
	switch (playerCount) {
	case 1: {
		inFile.open("../../src/data/maps/mapSingle.txt");
		break;
	}
	case 2: {
		inFile.open("../../src/data/maps/mapCoop2.txt");
		break;
	}
	case 3: {
		inFile.open("../../src/data/maps/mapCoop3.txt");
		break;
	}
	case 4: {
		inFile.open("../../src/data/maps/mapCoop4.txt");
		break;
	}
	}
	
	if (!inFile) {
		cout << "Unable to open file\n";
		return;
	}

	this->m_Map = createMap(inFile, playerCount);

	if (!inFile || !inFile.eof()) {
		cout << "Failed to read map from file\n";
		return;
	}
}


void CStorage::storeUnits() {
	ifstream inFile;
	inFile.open("../../src/data/units.txt");

	if (!inFile) {
		cout << "Unable to open file\n";
		return;
	}

	this->m_Units = createUnits(inFile);
	
	if (!inFile || !inFile.eof()) {
		cout << "Failed to read units from file\n";
		return;
	}
}
void CStorage::storeBuildings() {
	ifstream inFile;
	inFile.open("../../src/data/buildings.txt");

	if (!inFile) {
		cout << "Unable to open file\n";
		return;
	}

	this->m_Buildings = createBuildings(inFile);

	if (!inFile || !inFile.eof()) {
		cout << "Failed to read buildings from file\n";
		return;
	}

	ifstream infileImg;
	infileImg.open("../../src/data/imagesDef.txt");
	
	if (!infileImg) {
		cout << "Unable to open file\n";
		return;
	}
	addImages(infileImg);

	if (!infileImg || !infileImg.eof()) {
		cout << "Failed to read images from file\n";
		return;
	}
}

map<int, shared_ptr<CBuilding>> CStorage::printBuildings(bool isResource, CPlayer& player, const string& resource) const {
	int count = 0;
	map<int, shared_ptr<CBuilding>> choiceMap;
	for (auto it = this->m_Buildings.begin(); it != this->m_Buildings.end(); ++it) {
		if (isResource == true) {
			if (it->second->m_isResource == true && it->second->m_Lvl <= player.m_LVL && it->second->getResourceName() == resource && player.m_Gold >= it->second->m_Cost) {
				cout << "\nPress " << count << " to build this building:\n";
				it->second->print();
				choiceMap.emplace(count, it->second);
				++count;
			}
		}
		else {
			if ((it->second->m_Name == "keep" || it->second->m_Name == "castle") && haveRequirements(player.m_Resources, it->second->m_Requirements) && player.m_Gold >= it->second->m_Cost) {
				cout << "\nPress " << count << " to build this building:\n";
				it->second->print();
				choiceMap.emplace(count, it->second);
				++count;
				continue;
			}
			if (it->second->m_isResource == false && it->second->m_Lvl <= player.m_LVL && haveRequirements(player.m_Resources, it->second->m_Requirements) && player.m_Gold >= it->second->m_Cost)  {
				cout << "\nPress " << count << " to build this building:\n";
				it->second->print();
				choiceMap.emplace(count, it->second);
				++count;
			}
		}
	}
	return choiceMap;
}

void CStorage::printAllUnits() const{
	vector<shared_ptr<CUnit>> output;

	for (auto it = this->m_Units.begin(); it != this->m_Units.end(); ++it) {
		output.push_back(it->second);
	}

	sort(output.begin(), output.end(), compareUnit);
	for (size_t i = 0; i < output.size(); ++i) {
		output[i]->print();
		cout << endl;
	}
}


void CStorage::addImages(istream& imagesDef) {
	CTokenReader input(imagesDef);

	while (input && !input.eof()) {
		string find = input.readString(newLine);
		while (!input.isExpectedOrEof(newLine)) {
			this->m_Buildings[find]->m_Image.push_back(input.readString(newLine));
		}
	}
}

void CStorage::printAllBuildings(){
	vector<shared_ptr<CBuilding>> output;

	for (auto it = this->m_Buildings.begin(); it != this->m_Buildings.end(); ++it) {
		output.push_back(it->second);
	}

	sort(output.begin(), output.end(), compareBuilding);
	for (size_t i = 0; i < output.size(); ++i) {
		output[i]->print();
	}
}
