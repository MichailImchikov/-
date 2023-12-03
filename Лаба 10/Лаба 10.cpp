
#include <iostream>
#include<vector>
#include"StartPosition.h"
#include"ParansChoise.h"
#include "Crossover.h"
#include"Mutation.h"
#include "Assessment.h"
#include "NextPopul.h"
#include <iostream>
#include<fstream>

class MyStreambuf :public std::streambuf
{
public:
	MyStreambuf(std::streambuf* _firstBuf, std::streambuf* _secondBuf) :firstBuf(_firstBuf), secondBuf(_secondBuf) {}
	std::streamsize xsputn(const char_type* s, std::streamsize n)
	{
		firstBuf->sputn(s, n);
		secondBuf->sputn(s, n);
		return n;
	}

	int overflow(int_type c)
	{
		firstBuf->sputc(c);
		secondBuf->sputc(c);
		return c;
	}

private:
	std::streambuf* firstBuf;
	std::streambuf* secondBuf;
};
void StartPopulation(int SizeStartPop, int SizePack,float* Price, float* Weight, std::vector<std::vector<int>>& Population,int Oper,int MaxW )
{
		for (int i = 0; i < SizeStartPop; i++)
		{

			//Создаем рюкзак
			std::vector<int> buf=StartPosition(Price, Weight, SizePack, MaxW,Oper);
			//добавляем в рюкзак
			Population.push_back(buf);

		}
}
float P(std::vector<int>buf, float* Price)
{
	float sum = 0;
	for (int i = 0; i < buf.size(); i++)
	{
		if (buf[i] == 1)
		{
			sum += Price[i];
		}
	}
	return sum;
}
float W(std::vector<int>buf, float* Weight)
{
	float sum = 0;
	for (int i = 0; i < buf.size(); i++)
	{
		if (buf[i] == 1)
		{
			sum += Weight[i];
		}
	}
	return sum;
}
void PrintVec(std::vector<int>buf, float* Price, float* Weight)
{
	for (int i = 0; i < buf.size(); i++)
	{
		std::cout << buf[i];
	}
	std::cout << " P-" << P(buf, Price) << " W-" << W(buf, Weight);
}
std::vector<int> SelectBest(std::vector<std::vector<int>> Popul, float* Price, float* Weight)
{
	int max = 0;
	int Number = 0;
	for (int i = 0; i < Popul.size(); i++)
	{
		if (max < P(Popul[i], Price))
		{
			Number = i;
			max = P(Popul[i], Price);
		}
	}
	std::cout << "\nBEST: ";
	PrintVec(Popul[Number],Price,Weight);
	return Popul[Number];
}
class Statistic
{
public:
    int Sum = 0;
	int Count = 0;
	int minNN = 1000
		;
	int tact = -1;
	void CountStat(std::vector<std::vector<int>> Popul, float* Price)
	{
		for (int i = 0; i < Popul.size(); i++)
		{
			Sum += P(Popul[i], Price);
			Count++;
			if (P(Popul[i], Price) < minNN)
			{
				minNN = P(Popul[i], Price);
			}
		}
		tact++;
	}
	void PrintStat()
	{
		std::cout << "sred:" << Sum / Count << "tact" << tact << "min:" << minNN;
	}
};
int main()
{
	srand(time(0));
	//Настройка рюкзака
	Statistic stat;
	std::ofstream stream("test.txt");
	MyStreambuf streambuf(stream.rdbuf(), std::cout.rdbuf());
	std::cout.rdbuf(&streambuf);


	int SizePack = 0;
	int MaxW = 0;
	std::cout << "Enter the number of items: ";
	std::cin >> SizePack;
	float* Price = new float[SizePack];
	float* Weight = new float[SizePack];
	float SumW = 0;
	std::cout << " Price Weight  \n";
	for (int i = 0; i < SizePack; i++)
	{
		std::cout << i + 1 << ":  ";
		std::cin >> Price[i];
		std::cin >> Weight[i];
		SumW += Weight[i];
		
	}
	do
	{
		std::cout << "Enter Max Weight: ";
		std::cin >> MaxW;
	} while (MaxW > SumW);	

	//Настройка ЭГА

	int SizeStartPop = 0;
	int answer = 0;
	std::vector<int> Operator;
	std::vector<std::vector<int>> Parant;
	std::vector<std::vector<int>> Child;
	std::vector<std::vector<int>> Mutant;
	std::vector<int> BestResult;
	int maxIter = 0;

	//////////////////////////////

	std::cout << "\nEnter the population size: ";
	std::cin >> SizeStartPop;
	/////////////////////////////////
	std::cout << "Initial Population operator: \n<1-Heuristics>  <2-Heuristics Dansig>\n";
	std::cin >> answer;
	Operator.push_back(answer);//0-Стартовая популяция
	////////////////////////////
	std::cout << "Choosing a Parent Pair:\n<1-Random> <2-Positive Associative Mating>\n";
	std::cin >> answer;
	Operator.push_back(answer);//1-Выбор Родителей
	//////////////////////////////////
	std::cout << "Choosing a Crossover:\n<1-I_Point> <2-II_Point> <3-Homogeneous>\n";
	std::cin >> answer;
	Operator.push_back(answer);//2-Выбор Кроссовера
	/////////////////////////
	std::cout << "Choose the type of mutation:\n<1-Gene> <2-Saltation> <3-Chromosomal>\n";
	std::cin >> answer;
	Operator.push_back(answer);//3-Выбор мутации
	/////////////////////////
	std::cout << "Choose the evaluation method: \n<1-Elimination> <2-Genotype modification>\n";
	std::cin >> answer;
	Operator.push_back(answer);//4 -Выбор метода для оценки ограничений
	////////////////////
	std::cout << "Choose a strategy for the formation of the next generation: \n<1-elite> <2-m+y>\n";
	std::cin >> answer;
	Operator.push_back(answer);//5 -Выбор стратегии формирования
	////////////////////
	std::cout << "Select the selection method: \n<1-Proportional selection> <2-b-tournament>\n";
	std::cin >> answer;
	Operator.push_back(answer);//6 -Выбор селекции

	//START
	StartPopulation(SizeStartPop, SizePack,Price,Weight, Parant, Operator[0],MaxW);
	std::cout << "   GENERATION PATANTS: \n";
	for (int j = 0; j < Parant.size(); j++)
	{
		std::cout << j<<": ";
		PrintVec(Parant[j], Price, Weight);
		std::cout << "\n";
	}
	stat.CountStat(Parant, Price);

	while (maxIter!=5)
	{
		std::cout << "-----------------------------------------------------------------------------------------------------------------------";
		Child.clear();
		Mutant.clear();
		std::vector<int>buf = SelectBest(Parant, Price, Weight);
		if (BestResult != buf)
		{
			BestResult = buf;
			maxIter = 0;
		}
		else
		{
			maxIter++;	
		}
		// создадим потомство
		std::cout << "\n\n CREATE CHILD: \n";
		std::cin.ignore();
		for (int i = 0; i < SizeStartPop; i++)
		{

			int* arr = Parans(Parant, Operator[1], Price);
			std::cout <<"\n " << i << ": \n\n(" << arr[0] << "): ";
			PrintVec(Parant[arr[0]], Price, Weight);
			std::cout<<"\n     +\n(" << arr[1] << "): ";
			PrintVec(Parant[arr[1]], Price, Weight);
			std::cout << "\n     =\n     ";
			std::vector<int> buf = Crossover(arr, Operator[2], SizePack, Parant);
			delete arr;
			PrintVec(buf, Price, Weight);
			Child.push_back(buf);
		}
		// создадим мутантов с вероятностью 5%
		std::cout << "\n\n CREATE MUTANTS: \n";
		std::cin.ignore();
		Mutant = Mutation(Child, Operator[3]);
		if (Mutant.size() == 0)
		{
			std::cout<<"\nThe mutation did not occur\n";
			std::cout << "   ___   ___   \n";
			std::cout << "  | * | | * |  \n";
			std::cout << "   ---   ---   \n";
			std::cout << "      /        \n";
			std::cout << "      --        \n";
			std::cout << "    _-----_    \n";
			std::cout << "   -       -   ";
		}
		else
		{
			std::cout << "\nA mutation has occurred:\n";
			for (int i = 0; i < Mutant.size(); i++)
			{
				std::cout << i << ": ";
				PrintVec(Mutant[i], Price, Weight);
				std::cout << "\n";
			}
		}
		// этап оценки 
		std::cout << "\n\n LET'S EVALUATE THE RESULTS OBTAINED: \n";
		std::cin.ignore();
		Assessment(Child, Operator[4], MaxW, Weight);
		Assessment(Mutant, Operator[4], MaxW, Weight);
		std::cout << "Save CHILD:\n";
		for (int i = 0; i < Child.size(); i++)
		{
			std::cout << i << ": ";
			PrintVec(Child[i], Price, Weight);
			std::cout << "\n";
		}
		std::cout << "Save MUTANTS:\n";
		for (int i = 0; i < Mutant.size(); i++)
		{
			std::cout << i << ": ";
			PrintVec(Mutant[i], Price, Weight);
			std::cout << "\n";
		}
		// формируем новое поколение
		std::cout << "\n\n LET'S CREATE A NEW GENERATION: \n";
		std::cin.ignore();
		Parant = NextPopul(Parant, Child, Mutant, Operator, Price);
		for (int i = 0; i < SizeStartPop; i++)
		{
			std::cout << i << " ";
			PrintVec(Parant[i], Price, Weight);
			std::cout << "\n";
		}
		stat.CountStat(Parant, Price);

	}
	stat.PrintStat();

}
//15
//11 1
//18 25
//23 29
//21 24
//23 27
//30 21
//23 24
//3 13
//4 16
//6 15
//24 23
//2 14
//10 15
//15 3
//6 16
//106

