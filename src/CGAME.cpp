#include "CGAME.h"
#include <iostream>

using namespace std;

void CGame::saveMap(vector<vector<CTile>>& map, CTokenPutter& output) const{
	for (size_t i = 0; i < map.size(); ++i) {
		for (size_t j = 0; j < map[i].size(); ++j) {
			CTile tile = map[i][j];
			output.putBool(tile.m_Discovered);
			output.putDelimiter(' ');
			output.putBool(tile.m_IsEnemy);
			output.putDelimiter(' ');
			output.putBool(tile.m_IsResource);
			output.putDelimiter(' ');
			output.putBool(tile.m_IsBuilding);
			output.putDelimiter('\n');
			output.putInt(tile.m_Integrity);
			output.putDelimiter('\n');
			output.putString(tile.m_Description);
			output.putDelimiter('\n');
			for (size_t k = 0; k < tile.m_Tile.size(); ++k) {
				output.putString(tile.m_Tile[k]);
				output.putDelimiter('D');
			}
			output.putDelimiter('\n');
			if (tile.m_Building) {
				output.putString(tile.m_Building->m_Name);
				output.putDelimiter('\n');
			}
			if (tile.m_IsEnemy) {
				output.putInt(tile.m_Camp.m_Power);
				output.putDelimiter(' ');
				output.putInt(tile.m_Camp.m_Treasure);
				output.putDelimiter('\n');
				output.putString(tile.m_Camp.m_Captives->m_Name);
				output.putDelimiter(' ');
				output.putInt(tile.m_Camp.m_Captives->m_UnitSize);
				output.putDelimiter('\n');
			}
			output.putInt(tile.m_Position.m_X);
			output.putDelimiter(' ');
			output.putInt(tile.m_Position.m_Y);
			output.putDelimiter('\n');
			if (tile.m_IsResource == false && tile.m_IsEnemy == false) {
				for (size_t k = 0; k < 2; ++k) {
					for (size_t l = 0; l < 2; ++l) {
						CSmallTile smallTile = tile.m_SmallTiles[k][l];
						if (smallTile.m_Building) {
							output.putDelimiter('+');
							output.putString(smallTile.m_Building->m_Name);
							output.putDelimiter('\n');
						}
						else {
							output.putDelimiter('\n');
						}
						output.putBool(smallTile.m_Site);
						output.putDelimiter(' ');
						output.putBool(smallTile.m_Defense);
						output.putDelimiter('\n');
					}
				}
			}
		}
	}
}

void CGame::printMap() const {
	cout << " y/x         0               1               2               3               4               5               6               7       \n";
	for (int y = 0; y < 8; ++y) {
		cout << "     +---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
		for (int i = 0; i < 5; ++i) {
			if (i == 2) {
				cout << " " << y << "   |";
			}
			else {
				cout << "     |";
			}
			for (int x = 0; x < 8; ++x) {
				this->m_Storage.m_Map.m_Map[x][y].print(i);
				cout << "|";
				if (x == 7) {
					cout << endl;
				}
			}
		}
	}
	cout << "     +---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n\n";
}

void CGame::printBuildings() {
	cout << "\n List of all buildings:\n\n";
	this->m_Storage.printAllBuildings();
}

void CGame::printUnits() {
	cout << "\n List of all units:\n\n";
	this->m_Storage.printAllUnits();
}