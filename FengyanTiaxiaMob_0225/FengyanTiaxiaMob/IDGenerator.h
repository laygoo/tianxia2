#pragma once
#include "CommonUtil.h"
class IDGenerator
{
private:
	
public:
	IDGenerator();
	~IDGenerator();
	int Finish_ID[20];
	int l = 0;

	void IDGenerator::split(int Number, int count, int temprary);
	char IDGenerator::GetKeyNum(int Finish_ID[]);
	string IDGenerator::getIDNumber();
	int IDGenerator::Digit(int Number);
};

