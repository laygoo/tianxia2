#include "IDGenerator.h"



IDGenerator::IDGenerator()
{
}


IDGenerator::~IDGenerator()
{
}

void IDGenerator::split(int Number, int count, int temprary)
{

	int k = l;
	temprary = temprary / 10;
	for (l; l<k + count; l++)
	{
		if (temprary == 0) {
			return;
		}
		Finish_ID[l] = Number / temprary;


		Number = Number%temprary;
		temprary = temprary / 10;
	}
	return;
}

char IDGenerator::GetKeyNum(int Finish_ID[])
{
	char keyword;

	char Right_Val[20] = { '1','0','X','9','8','7','6','5','4','3','2' };

	int Cmp_ID[20] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };
	int Sum_ID = 0;
	int Temp_ID[20];//用来临时存储乘后数据  


	for (int i = 0; i<17; i++)
	{
		Temp_ID[i] = Cmp_ID[i] * Finish_ID[i];
	}

	for (int i = 0; i<17; i++)
	{
		Sum_ID = Sum_ID + Temp_ID[i];
	}

	Sum_ID = Sum_ID % 11;
	keyword = Right_Val[Sum_ID];
	return keyword;
}

string IDGenerator::getIDNumber() {
	srand((unsigned)time(NULL));
	l = 0;
	memset(Finish_ID, 0x0, 20 * sizeof(int));

	int Addr_ID;    //110000-659001  110000 + rand()%549001  

	int Year_ID;    //1900-1996     1900 + rand()%97  
	int Month_ID;   //01-12         1 + rand()%11  
	int Day_ID;     //01-28         1 + rand()%27  

	int Key_ID;     //100-999       100+rand()%899  

	int Cmp_ID;

	Addr_ID = (1 + rand() % 5) * 100000 + (1 + rand() % 2) * 10000; CommonUtil:Digit(Addr_ID);
	Year_ID = 1980 + rand() % 17; Digit(Year_ID);
	Month_ID = 10 + rand() % 2; Digit(Month_ID);
	Day_ID = 10 + rand() % 17; Digit(Day_ID);
	Key_ID = 100 + rand() % 899; Digit(Key_ID);


	char keyword;
	keyword = GetKeyNum(Finish_ID);
	string temp = "";

	for (int i = 0; i<17; i++)
	{
		cout << Finish_ID[i];
		temp.append(CommonUtil::char2string1(Finish_ID[i]));
	}

	temp.append(CommonUtil::char2string(keyword));

	return temp;
}

int IDGenerator::Digit(int Number)
{
	int temprary = 1;
	int count = 0;
	while (1)
	{
		if (Number  <    temprary)
		{
			count++;
			goto outport;
		}
		else
		{
			temprary = temprary * 10;
			count++;
		}
	}
outport:
	count--;
	split(Number, count, temprary);
	return count;
}