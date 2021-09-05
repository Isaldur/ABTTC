#include "CMap.h"
#include "CDefenseBuilding.h"
#include "CAlly.h"


void CMap::createTile(int x, int y, const string& description, int playerCount) {
	CTile newTile;

	switch (playerCount){
	case 4: {
		if (x > 5 && y > 5) {
			newTile.m_Discovered = true;
		}
	}
	case 3: {
		if (x < 2 && y > 5) {
			newTile.m_Discovered = true;
		}
	}
	case 2: {
		if (x > 5 && y < 2) {
			newTile.m_Discovered = true;
		}
	}
	case 1: {
		if (x < 2 && y < 2) {
			newTile.m_Discovered = true;
		}
		break;
	}
	}

	if (description == "start") {
		vector<CResource> empty;
		newTile.m_SmallTiles[0][0].m_Building = make_shared<CDefenseBuilding>(400, 1, false, 100, 50, "settlement", "keep", empty);
		newTile.m_Description = "Starting position";
		newTile.m_Integrity = 3;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("    Starting   ");
		newTile.addRow("   Settlement  ");
		newTile.addRow("  _   ___  &   ");
		newTile.addRow(" / \\ /___\\  &  ");
		newTile.addRow(" | | |   |/\\/\\ ");
		newTile.m_SmallTiles[0][0].addRow("Settlement  |_|_|_|_|          ");
		newTile.m_SmallTiles[0][0].addRow("LVL 1       |       |          ");
		newTile.m_SmallTiles[0][0].addRow("            |       |          ");
		newTile.m_SmallTiles[0][0].addRow("            |       |          ");
		newTile.m_SmallTiles[0][0].addRow("   /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\  ");
		newTile.m_SmallTiles[0][0].addRow("   ||||||||||||||||||||||||||  ");
		newTile.m_SmallTiles[0][0].addRow("   ||||||||||||||||||||||||||  ");
		newTile.m_SmallTiles[0][0].addRow("   ||||||||||||||||||||||||||  ");
		newTile.m_SmallTiles[0][0].addRow("   ||||||||||       |||||||||  ");
		newTile.m_SmallTiles[0][0].addRow("   ||||||||||       |||||||||  ");
		newTile.m_SmallTiles[0][0].m_Defense = true;
		newTile.m_SmallTiles[0][1].makeSite();
		newTile.m_SmallTiles[1][0].makeSite();
		newTile.m_SmallTiles[1][1].makeSite();
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "enemy") {
		newTile.m_Description = "Enemy Camp";
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("   Enemy camp  ");
		newTile.addRow(" /\\/\\/\\/\\/\\/\\  ");
		newTile.addRow(" |  &    o   | ");
		newTile.addRow(" |   &  /|\\  | ");
		newTile.addRow(" | /\\/\\  |   | ");
		newTile.m_IsEnemy = true;
		newTile.m_Camp.m_Power = 1000;
		newTile.m_Camp.m_Captives = make_shared<CAlly>(4, 42, 3, 3, 6, 0, "crossbows");
		newTile.m_Camp.m_Treasure = 1000;
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "field") {
		newTile.m_Description = description;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("     Field     ");
		newTile.addRow(" ----------*-- ");
		newTile.addRow(" ---*------|-- ");
		newTile.addRow(" ------------- ");
		newTile.addRow(" ------------- ");
		newTile.m_SmallTiles[0][0].makeSite();
		newTile.m_SmallTiles[0][1].makeSite();
		newTile.m_SmallTiles[1][0].makeSite();
		newTile.m_SmallTiles[1][1].makeSite();
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "forest") {
		newTile.m_Description = description;
		newTile.m_IsResource = true;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("     Forest    ");
		newTile.addRow("      /\\       ");
		newTile.addRow("  /\\ /||\\      ");
		newTile.addRow(" /||\\/||\\\\ v   ");
		newTile.addRow("  ||  ||  \\|/  ");
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "stone") {
		newTile.m_Description = description;
		newTile.m_IsResource = true;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("     Stone     ");
		newTile.addRow("  ___    __    ");
		newTile.addRow("  \\  \\__/  \\   ");
		newTile.addRow("  /  /  \\  /\\  ");
		newTile.addRow(" /   \\  /  \\ \\ ");
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "iron") {
		newTile.m_Description = description;
		newTile.m_IsResource = true;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("      Iron     ");
		newTile.addRow("    _______    ");
		newTile.addRow("   / /\\   /\\   ");
		newTile.addRow("  /\\/  \\ /  \\  ");
		newTile.addRow(" /  \\   /    \\ ");
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "gold") {
		newTile.m_Description = description;
		newTile.m_IsResource = true;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("      Gold     ");
		newTile.addRow("    _______    ");
		newTile.addRow("   / /\\$$$/\\   ");
		newTile.addRow("  /\\/$$\\ /$$\\  ");
		newTile.addRow(" /$$\\$$$/$$$$\\ ");
		this->m_Map[x][y] = newTile;
		return;
	}
	else if (description == "horses") {
		newTile.m_Description = description;
		newTile.m_IsResource = true;
		newTile.m_Position.m_X = x;
		newTile.m_Position.m_Y = y;
		newTile.addRow("     Horses    ");
		newTile.addRow("    ____;///-; ");
		newTile.addRow(" ,~(  ) ,)~~\\| ");
		newTile.addRow(" ' / / -`--,   ");
		newTile.addRow("  /  \\   | '   ");
		this->m_Map[x][y] = newTile;
		return;
	}
}