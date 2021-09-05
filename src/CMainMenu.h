#pragma once
#include "CInterface.h"
#include "CGameptr.h"
#include "CTile.h"
#include "CSmallTile.h"
#include "CEnemyCamp.h"
#include "CPlayer.h"
#include "CTokenReader.h"

class CMainMenu : public CInterface{
public:
	CMainMenu() = default;
	~CMainMenu() = default;

	void printMenu() override;
	void execute();
	void loadGame(CGamePtr&);
	void createGame(CGamePtr&, ifstream&);
	vector<vector<CTile>> readMap(CTokenReader&, CGamePtr&);
	CSmallTile readSmallTile(CTokenReader&, CGamePtr&);
	CEnemyCamp readEnemy(CTokenReader&, CGamePtr&);

	bool notAgain = false;
};

