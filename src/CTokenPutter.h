#pragma once
#include <ostream>
#include <string>

using namespace std;

class CTokenPutter{
	ostream& m_os;
public:
	CTokenPutter(ostream& os) : m_os(os) {}

	void putDelimiter(char);
	void putString(const string&);
	void putInt(int);
	void putBool(bool);
};

