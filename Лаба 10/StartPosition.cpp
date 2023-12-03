#include "StartPosition.h"
#include <iostream>
#include<vector>
int RandomPrice(float* Price, float Size, bool* way)
{
	int SumPriceP = 0;
	for (int i = 0; i < Size; i++)
	{
		if (way[i])
		{
			SumPriceP += Price[i];
		}
	}
	int x = rand() % (SumPriceP)+1;
	for (int i = 0; i < Size; i++)
	{
		if (way[i])
		{
			x -= Price[i];
			if (x <= 0)
			{
				return i;
			}
		}
	}

}
int RandomRelativeValue(float* Price, float* Weight, int Size, bool* flag)
{
	float SumPriceP = 0;
	for (int i = 0; i < Size; i++)
	{
		if (flag[i])
		{
			SumPriceP += (float)Price[i] / Weight[i];
		}
	}
	float x = (float)(rand()) / RAND_MAX * SumPriceP;
	for (int i = 0; i < Size; i++)
	{
		if (flag[i])
		{
			x -= (float)Price[i] / Weight[i];
			if (x <= 0)
			{
				return i;
			}
		}
	}
}
std::vector<int> StartPosition(float* Price, float* Weight, int Size,int MaxW,int Oper)
{
	std::vector<int> buf;
	bool* Way = new bool[Size];
	for (int i = 0; i < Size; i++)
	{
		Way[i] = true;
		buf.push_back(0);
	}
	int SumW = 0;
	for (int i = 0; i < Size; i++) {
		int index = 0;
		//выбор оператора
		if (Oper == 1)
		{
			index = RandomPrice(Price, Size, Way);
		}
		else
		{
			index = RandomRelativeValue(Price,Weight, Size, Way);
		}
		 //проверка
		if (SumW + Weight[index] > MaxW)
		{
			Way[index] = false;
		}
		else
		{
			SumW += Weight[index];
			buf[index] = 1;
			Way[index] = false;
			}
		}	
	return  buf;
}
