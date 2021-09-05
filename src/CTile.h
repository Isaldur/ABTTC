#pragma once
#include "CEnemyCamp.h"
#include "CPosition.h"
#include "CSmallTile.h"
#include "CGameptr.h"
#include <vector>
#include <string>

using namespace std;

class CTile {
public:
	CTile() = default;
	~CTile() = default;

	void addRow(const string&);
	void print(int) const;
	void printZoom() const;
	void printResourceTile();
	void printEnemyTile();
	bool canExplore(CGamePtr&);

	bool m_Discovered = false;
	bool m_IsEnemy = false;
	bool m_IsBuilding = false;
	bool m_IsResource = false;

	int m_Integrity = 2;
	shared_ptr<CBuilding> m_Building;
	string m_Description;	// used to quickly identify type of tile
	vector<string> m_Tile;
	CPosition m_Position;
	CEnemyCamp m_Camp;
	CSmallTile m_SmallTiles[2][2];
};