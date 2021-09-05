#pragma once
#include "CInterface.h"
#include "CGameptr.h"
#include "CPlayer.h"
#include "CBuilding.h"
#include <memory>

class CBuildMenu : public CInterface {
public:
	void printMenu()override{}
	shared_ptr<CBuilding> printMenu(CGamePtr&, CPlayer&);
	shared_ptr<CBuilding> printResourceMenu(CGamePtr&, CPlayer&, const string&);
	shared_ptr<CBuilding> upgradeMenu(CGamePtr&, CPlayer&, shared_ptr<CBuilding>);

	map<int, shared_ptr<CBuilding>> choiceMap;
};