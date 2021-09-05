#pragma once
#include "CInterface.h"
#include "CGameptr.h"
#include "CBuildMenu.h"
#include "CTile.h"
#include <memory>

// this class represents ingame buildphase interface
using namespace std;

class CBuildPhaseMenu : public CInterface{
public:
	CBuildPhaseMenu() = default;
	~CBuildPhaseMenu() = default;

	void printMenu()override {}
	void printMenu(CGamePtr&, CPlayer&);
	void printUnitMenu(CGamePtr&, CPlayer&);
	void printAttackMenu(CGamePtr&, CPlayer&, CTile&);
	void execute(CGamePtr&, CPlayer&);
	void build(CGamePtr&, CPlayer&);
	void train(CGamePtr&, CPlayer&);
	void explore(CGamePtr&, CPlayer&);
	void attack(CGamePtr&, CPlayer&);
	void showMap(CGamePtr&);
	void showStats(CPlayer&);
	void endTurn(CGamePtr&, CPlayer&);

	CBuildMenu buildMenu;
	bool assault = false;
	bool endedTurn = false;
};

