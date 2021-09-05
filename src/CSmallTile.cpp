#include "CSmallTile.h"
#include <iostream>

using namespace std;

void CSmallTile::print(int row) const{
	if (this->m_Site == true) {
		cout << this->m_Image[row];
	}
	else {
		cout << this->m_Building->m_Image[row];
	}
}

void CSmallTile::addRow(const string& row){
	this->m_Building->m_Image.push_back(row);
}

void CSmallTile::makeSite() {
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("         TO BUILD HERE         ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Image.push_back("                               ");
	this->m_Site = true;
}