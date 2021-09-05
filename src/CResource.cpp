#include "CResource.h"

bool CResource::operator>=(const CResource& other) const{
	if (this->m_Level >= other.m_Level && this->m_Name == other.m_Name) {
		return true;
	}
	return false;
}