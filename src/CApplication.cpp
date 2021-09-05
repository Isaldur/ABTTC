#include "CApplication.h"

using namespace std;

void CApplication::run() {
	while (this->m_Menu.notAgain == false) {
		this->m_Menu.execute();
	}
}
