#pragma once
#include <istream>
#include <string>

using namespace std;

class CTokenReader {
	istream& m_is;
public:
	CTokenReader(istream& is) : m_is(is) {}

	void readDelimiter(char delim);
	string readString(char delim);
	int readInt();
	bool isExpected(char ch);
	bool isExpectedOrEof(char ch);
	operator bool() const;
	bool eof() const;
};