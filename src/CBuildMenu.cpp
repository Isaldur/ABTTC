#include "CBuildMenu.h"
#include "CGAME.h"

shared_ptr<CBuilding> CBuildMenu::printMenu(CGamePtr& thisGame, CPlayer& player) {
	cout << "\n Available buildings:\n\n";
	this->choiceMap = thisGame->m_Storage.printBuildings(false, player);
	if (choiceMap.size() == 0) {
		cout << "\n No available buildings. Try to earn more gold, resources or try to upgrade your settlement. ( check list of buildings )\n";
		return {};
	}
	cout << " Press -1 to return\n";
	this->choice = getchoice(-1, (int)choiceMap.size() - 1);
	if (choice == -1) {
		return {};
	}
	player.m_Gold = player.m_Gold - this->choiceMap[this->choice]->m_Cost;
	this->choiceMap[this->choice]->updateIncome(player);
	return this->choiceMap[this->choice];
}

shared_ptr<CBuilding> CBuildMenu::printResourceMenu(CGamePtr& thisGame, CPlayer& player, const string& resource) {
	cout << "\n Available buildings:\n\n";
	this->choiceMap = thisGame->m_Storage.printBuildings(true, player, resource);
	if (choiceMap.size() == 0) {
		cout << "\n No available buildings. Try to earn more gold, choose different resource or try to upgrade your settlement. ( check list of buildings )\n";
		return {};
	}
	cout << " Press -1 to return\n";
	this->choice = getchoice(-1, (int)choiceMap.size() - 1);
	if (choice == -1) {
		return {};
	}
	player.m_Gold -= this->choiceMap[this->choice]->m_Cost;
	this->choiceMap[this->choice]->updateIncome(player);
	this->choiceMap[this->choice]->updateResources(player);

	return this->choiceMap[this->choice];
}

shared_ptr<CBuilding> CBuildMenu::upgradeMenu(CGamePtr& thisGame, CPlayer& player, shared_ptr<CBuilding> building) {
	if (building->m_Upgrade.empty()) {
		cout << "\n This building is at max LVL.\n\n";
		return {};
	}
	shared_ptr<CBuilding> better;
	better = thisGame->m_Storage.m_Buildings[building->m_Upgrade];
	if (player.m_Gold >= (better->m_Cost - building->m_Cost) && haveRequirements(player.m_Resources, better->m_Requirements) && (player.m_LVL >= better->m_Lvl || better->m_Name == "keep" || better->m_Name == "castle")) {
		cout << "\n Building available for upgrade:\n\n";
		cout << "\n Press 0 to build this building:\n";
		better->print();
		cout << " Press -1 to return\n";
		this->choice = getchoice(-1, 0);
		if (choice == -1) {
			return {};
		}
		player.m_Gold -= better->m_Cost;
		player.m_Gold += building->m_Cost;
		player.m_Income -= building->getIncome();
		better->updateIncome(player);
		better->updateResources(player);
		if (better->m_Name == "keep" || better->m_Name == "castle") {
			better->updateLvL(player);
		}
		return better;
	}
	cout << "\n Need more gold, resources or LVL ( check list of buildings )\n\n";
	return {};
}