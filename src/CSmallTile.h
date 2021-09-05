#pragma once
#include <vector>
#include <string>
#include "CBuilding.h"
#include <memory>
using namespace std;

// this class represents zoomed tile with ascii art in it

class CSmallTile{
public:
	CSmallTile() = default;
	~CSmallTile() = default;

	void print(int) const;
	void addRow(const string&);
	void makeSite();

	vector<string> m_Image;
	shared_ptr<CBuilding> m_Building;
	bool m_Site = false;
	bool m_Defense = false;
};

