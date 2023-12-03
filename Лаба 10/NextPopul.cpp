#include "NextPopul.h"
#include "Selection.h"
#include <vector>
#include <iostream>
float Presss(std::vector<int>buf, float* Price)
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
std::vector<std::vector<int>> NextPopul(std::vector<std::vector<int>> Parants, std::vector<std::vector<int>> Child, std::vector<std::vector<int>> Mutant, std::vector<int> Oper,float*Price)
{
    int size = Parants.size();
    std::vector<std::vector<int>> buf;
    if (Oper[5] == 1)
    {
        for (int i = 0; i < Child.size(); i++)
        {
            Parants.push_back(Child[i]);
        }
        for (int i = 0; i < Mutant.size(); i++)
        {
            Parants.push_back(Mutant[i]);
        }
        int Max = 0;
        std::vector<int> max;
        for (int i = 0; i < Parants.size(); i++)
        {
            if (Presss(Parants[i],Price) > Max)
            {
                Max = Presss(Parants[i], Price);
                max = Parants[i];
            }
        }
        buf = Selection(Parants, Oper[6], Price, size);
        bool flag = false;
        for (int i = 0; i < buf.size(); i++)
        {
            if (buf[i] == max)
            {
                flag = true;
            }
        }
        if (!flag)
        {
            buf.pop_back();
            buf.push_back(max);
        }
        
    }
    if (Oper[5] == 2)
    {
        std::vector<std::vector<int>> buf1;
        std::vector<std::vector<int>> buf2;
        for (int i = 0; i < Mutant.size(); i++)
        {
            Child.push_back(Mutant[i]);
        }
            buf1 = Selection(Parants, Oper[6], Price, Parants.size()- Child.size() / 2);
            buf2 = Selection(Child, Oper[6], Price, Child.size() / 2);

        for (int i = 0; i < buf1.size(); i++)
        {
            buf.push_back(buf1[i]);
        }
        for (int i = 0; i < buf2.size(); i++)
        {
            buf.push_back(buf2[i]);
        }
    }
    return buf;
}

