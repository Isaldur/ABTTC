#pragma once
#include <string>

using namespace std;

class CResource{
public:
	CResource() = default;
	~CResource() = default;
	
	bool operator>=(const CResource&) const;

	int m_Level = 0;    // level of resources is determined by level of resource buildings
	string m_Name;
};

