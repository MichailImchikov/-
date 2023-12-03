#include "Crossover.h"
#include <vector>
#include <iostream>
std::vector<int> Crossover(int* arr, int Oper,int Size, std::vector<std::vector<int>>Popul)
{
    std::vector<int> buf;
    if (Oper == 1)
    {
        for (int i = 0; i < Size / 2; i++)
        {
            buf.push_back(Popul[arr[0]][i]);
        }
        for (int i = Size / 2; i < Size; i++)
        {
            buf.push_back(Popul[arr[1]][i]);
        }
    }
    if (Oper == 2)
    {
        for (int i = 0; i < Size / 3; i++)
        {
            buf.push_back(Popul[arr[0]][i]);
        }
        for (int i = Size / 3; i < 2*Size / 3; i++)
        {
            buf.push_back(Popul[arr[1]][i]);
        }
        for (int i = 2 * Size / 3; i < Size ; i++)
        {
            buf.push_back(Popul[arr[0]][i]);
        }
    }
    if (Oper == 3)
    {
        for (int i = 0; i < Size; i++)
        {
            if (rand() % 2 == 0)
            {
                buf.push_back(Popul[arr[1]][i]);
            }
            else
            {
                buf.push_back(Popul[arr[0]][i]);
            }
        }
    }
    return buf;
}
