#pragma once
#include "CScout.h"
#include <memory>

using namespace std;

class CScoutAway {
public:
	CScoutAway() = default;
	~CScoutAway() = default;
	
	CScout m_Scout;
	int m_TimeLeft = 0;
};