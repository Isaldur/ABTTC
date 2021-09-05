#pragma once
#include "CAlly.h"
#include <memory>

class CEnemyCamp{
public:
	CEnemyCamp() = default;
	~CEnemyCamp() = default;

	int m_Power = 0,	// power needed to destroy the camp
	    m_Treasure = 0;
	shared_ptr<CUnit> m_Captives;
};