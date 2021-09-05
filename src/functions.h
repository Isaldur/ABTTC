#pragma once
#include "CPlayer.h"
#include "CScout.h"
#include "CAlly.h"
#include "CBuilding.h"
#include "CResource.h"
#include <iostream>

int getchoice(int low, int high);
CPlayer createPlayer(int difficulty);

void insertUnit(shared_ptr<CUnit>, map<string, shared_ptr<CUnit>>&);
void insertBuilding(shared_ptr<CBuilding>, map<string, shared_ptr<CBuilding>>&);

bool haveRequirements(const vector<CResource>&, const vector<CResource>&);

bool compareBuilding(const shared_ptr<CBuilding>&, const shared_ptr<CBuilding>&);
bool compareUnit(const shared_ptr<CUnit>&, const shared_ptr<CUnit>&);
bool compareSurvivors(const CAlly&, const CAlly&);