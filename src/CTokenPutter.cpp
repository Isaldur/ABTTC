#include "CTokenPutter.h"

void CTokenPutter::putDelimiter(char delim){
	this->m_os << delim;
}

void CTokenPutter::putString(const string& token){
	this->m_os << token;
}

void CTokenPutter::putInt(int token){
	this->m_os << token;
}

void CTokenPutter::putBool(bool token){
	if (token == false) {
		this->m_os << 0;
	}
	else {
		this->m_os << 1;
	}
}
