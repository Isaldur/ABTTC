#pragma once
class CPosition{
public:
	CPosition() = default;
	CPosition(int x, int y) : m_X(x), m_Y(y){}
	~CPosition() = default;
	
	int m_X = 0,
		m_Y = 0;
};

