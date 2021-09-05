#pragma once
#include "CGAME.h"
#include "CMainMenu.h"
#include <string>
#include <vector>

using namespace std;

// this class runs the game and operates the main menu

class CApplication{
public:
	CApplication() = default;
	~CApplication() = default;

	void run();

private:
	CMainMenu m_Menu;
	int choice = 0;		//used for working with user input represented by number
};