#pragma once
#include "CTile.h"
#include <vector>
#include <string>

using namespace std;
class CMap{
public:
	CMap() = default;
	CMap(const CMap&) = default;
	~CMap() = default;

	CMap& operator=(const CMap& other) {
		this->m_Map = other.m_Map;
		return *this;
	}

	void createTile(int, int, const string&, int);

	vector<vector<CTile>> m_Map;
};

