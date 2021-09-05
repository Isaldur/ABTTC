#include "CTile.h"
#include "CGAME.h"
#include <ostream>
#include <iostream>
using namespace std;

void CTile::addRow(const string& row) {
	this->m_Tile.push_back(row);
}

void CTile::print(int row) const {
	string hidden = "               ";
	if (this->m_Discovered == false) {
		cout << hidden;
	}
	else {
		cout << this->m_Tile[row];
	}
}

void CTile::printZoom() const {
	cout << "\ny/x                      0                             1                \n";
	for (int i = 0; i < 2; ++i) {
		cout << "        +-------------------------------+-------------------------------+\n";
		for (int j = 0; j < 10; ++j) {
			if (j == 4) {
				cout << i << "       |";
			}
			else {
				cout << "        |";
			}
				this->m_SmallTiles[0][i].print(j);
				cout << "|";
				this->m_SmallTiles[1][i].print(j);
				cout << "|\n";
		}
	}
	cout << "        +-------------------------------+-------------------------------+\n";
}

void CTile::printResourceTile(){
	if (this->m_IsBuilding == true) {
		cout << "\n This building is built here: \n";
		this->m_Building->print();
	}
	else {
		cout << "\n This place can provide resource " << this->m_Description << ".\n\n";
	}
}

void CTile::printEnemyTile(){
	cout << "\n This enemy camp has:\n";
	cout << " Power: " << this->m_Camp.m_Power << endl;
	cout << " Treasure: " << this->m_Camp.m_Treasure << endl;
	cout << " Captives: \n\n";
	this->m_Camp.m_Captives->print();
	cout << endl;
	cout << endl;
}

bool CTile::canExplore(CGamePtr& game) {
	vector<vector<CTile>> tmpMap = game->m_Storage.m_Map.m_Map;
	if (tmpMap[this->m_Position.m_X][this->m_Position.m_Y].m_Discovered) {
		return false;
	}
	else {
		// CORNERS of the map ( other than start )
		if (m_Position.m_X == 0 && m_Position.m_Y == 7) {
			if (tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered) {
				return true;
			}
		}
		else if (m_Position.m_X == 7 && m_Position.m_Y == 7) {
			if (tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered) {
				return true;
			}
		}
		else if (m_Position.m_X == 7 && m_Position.m_Y == 0) {
			if (tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y + 1].m_Discovered) {
				return true;
			}
		}
		// SIDES of the map 
		else if ((m_Position.m_X > 0 && m_Position.m_X < 7) && m_Position.m_Y == 0) {
			if (tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y].m_Discovered) {
				return true;
			}
		}
		else if ((m_Position.m_Y > 0 && m_Position.m_Y < 7) && m_Position.m_X == 0) {
			if (tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y + 1].m_Discovered) {
				return true;
			}
		}
		else if ((m_Position.m_X > 0 && m_Position.m_X < 7) && m_Position.m_Y == 7) {
			if (tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y].m_Discovered) {
				return true;
			}
		}
		else if ((m_Position.m_Y > 0 && m_Position.m_Y < 7) && m_Position.m_X == 7) {
			if (tmpMap[m_Position.m_X][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered) {
				return true;
			}
		}
		else {   // CENTER tiles of the map
			if (tmpMap[m_Position.m_X - 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y - 1].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y].m_Discovered || tmpMap[m_Position.m_X + 1][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X][m_Position.m_Y + 1].m_Discovered || tmpMap[m_Position.m_X - 1][m_Position.m_Y + 1].m_Discovered) {
				return true;
			}
		}
	}
	return false;
}
