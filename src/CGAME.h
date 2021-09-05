#pragma once
#include "CStorage.h"
#include "CDefensePhase.h"
#include "CBuildPhaseMenu.h"
#include "CTokenPutter.h"
#include "CTokenReader.h"
#include <fstream>

// blueprint for classes CSingleGame and CCoopGame to operate the game

using namespace std;
class CGame{
public:
	virtual ~CGame() {}
	
	virtual void welcome()const = 0;
	virtual void addDifficulty() = 0;
	virtual void addPlayers() = 0;
	virtual void start() = 0;
	virtual void GAMEOVER() const = 0;
	virtual void VICTORY() const = 0;
	virtual void savegame() = 0;
	virtual void loadPlayers(CTokenReader&) = 0;
	void saveMap(vector<vector<CTile>>&, CTokenPutter&)const;
	void printMap()const;
	void printBuildings();
	void printUnits();

	CStorage m_Storage;
	CDefensePhase m_DefPhase;
	CBuildPhaseMenu m_BuildPhase;
	int m_Turn = 1,
		m_Round = 1,
		m_Difficulty = 0,
	    m_PlayerCount = 0;
	bool isCoop = false,
	     loaded = false;
};

