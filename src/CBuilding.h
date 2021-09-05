#pragma once
#include "CResource.h"
#include "CPlayer.h"
#include <string>
#include <vector>

using namespace std;

// this class is a blueprint for other building classes like CResourceBuilding etc.

class CBuilding{
public:
	CBuilding(int cost, int lvl, bool isResource, string name, string upgrade) : m_Cost(cost), m_Lvl(lvl), m_isResource(isResource), m_Name(move(name)), m_Upgrade(move(upgrade)) {}
	CBuilding(int cost, int lvl, bool isResource, string name, string upgrade, vector<CResource> requirements): m_Cost(cost), m_Lvl(lvl), m_isResource(isResource), m_Name(move(name)), m_Upgrade(move(upgrade)), m_Requirements(move(requirements)){}
	virtual ~CBuilding() {};

	virtual void print() const = 0;
	virtual void updateIncome(CPlayer&)const = 0;
	virtual void updateResources(CPlayer&)const = 0;
	virtual void updateLvL(CPlayer&) const = 0;
	virtual string getResourceName()const = 0;
	virtual int getIncome() const = 0;
	virtual int getPower() const = 0;
	virtual int getFirstStrike() const = 0;
	virtual CResource getResource() const = 0;
	
	int m_Cost = 0,
		m_Lvl = 0;						
	bool m_isResource = false;			
	string m_Name,						// used to quickly determine type of building
		   m_Upgrade;					// name of building to which is this upgraded
	vector<CResource> m_Requirements;	// resources needed to build
	vector<string> m_Image;				// ASCII art image
};

