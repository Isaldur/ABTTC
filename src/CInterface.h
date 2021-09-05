#pragma once
#include <vector>

using namespace std;
class CInterface{
public:
	virtual ~CInterface() {};

	virtual void printMenu() = 0;

	int choice = 0;
};