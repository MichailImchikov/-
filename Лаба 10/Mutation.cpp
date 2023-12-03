#include "Mutation.h"
#include <vector>
#include <iostream>
std::vector<std::vector<int>> Mutation(std::vector<std::vector<int>> popul, int Oper)
{
    std::vector<std::vector<int>> buf;
    if (Oper == 1)
    {
        for (int i = 0; i < popul.size(); i++)
        {
            if (rand() % 100 < 5)
            {
                std::vector<int> go = popul[i];
                int gen = rand() % popul[0].size();
                go[gen]=go[gen] == 1 ? 0 : 1;
                buf.push_back(go);
            }
        }
    }
    if (Oper == 2)
    {
        for (int i = 0; i < popul.size(); i++)
        {
            if (rand() % 100 < 5)
            {
                std::vector<int> go = popul[i];
                go[popul[0].size() - 2]=go[popul[0].size() - 2] == 1 ?  0 : 1;
                go[1]=go[1] == 1 ? 0 : 1;
                buf.push_back(go);
            }
        }
    }
    if (Oper == 3)
    {
        for (int i = 0; i < popul.size(); i++)
        {
            if (rand() % 100 < 5)
            {
                std::vector<int> go = popul[i];
                for (int j = 0; j < popul[0].size(); j++)
                {
                    
                    go[j] = go[j] == 1 ? 0 : 1;
                    
                }
                buf.push_back(go);
            }
        }
    }
    return buf;
}
