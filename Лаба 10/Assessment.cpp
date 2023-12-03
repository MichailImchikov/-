#include "Assessment.h"
#include <vector>
#include <iostream>
bool Assessment(std::vector<std::vector<int>>& popul, int Oper, int MaxW, float* Weight)
{
    bool flag = false;
    if (Oper == 1)
    {
        for (int i = 0; i < popul.size(); i++)
        {
            float sum = 0;
            for (int j = 0; j < popul[0].size(); j++)
            {
                sum += popul[i][j] == 1 ? Weight[j] : 0;
            }
            
            if (sum > MaxW)
            {
                popul.erase(popul.cbegin() + i);
                flag = true;
                i--;
            }
            
        }
    }
    if (Oper == 2)
    {
        for (int i = 0; i < popul.size(); i++)
        {
            float sum = 0;
            do 
            {
                sum = 0;
                for (int j = 0; j < popul[0].size(); j++)
                {
                    sum += popul[i][j] == 1 ? Weight[j] : 0;
                }
                if (sum > MaxW)
                {
                    popul[i][rand() % popul[0].size()] = 0;
                }
            } while (sum > MaxW);
    
        }
    }
    return flag;
}
