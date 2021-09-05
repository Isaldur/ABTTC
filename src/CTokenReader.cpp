#include "CTokenReader.h"

void CTokenReader::readDelimiter(char delim) {
	if (m_is && m_is.get() != delim) {
		m_is.setstate(ios_base::failbit);
	}
}

string CTokenReader::readString(char delim) {
	string result;
	getline(m_is, result, delim);
	return result;
}

int CTokenReader::readInt() {
	int result = 0;
	m_is >> result;
	return result;
}

bool CTokenReader::isExpected(char ch) {
	if (!m_is.eof() && m_is.peek() == ch) {
		m_is.ignore();
		return true;
	}
	return false;
}

bool CTokenReader::isExpectedOrEof(char ch) {
	return m_is.eof() || isExpected(ch);
}

CTokenReader::operator bool() const {
	return bool(m_is);
}

bool CTokenReader::eof() const {
	return m_is.eof();
}