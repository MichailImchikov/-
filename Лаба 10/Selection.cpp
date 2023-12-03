#include "Selection.h"
#include <vector>
#include <iostream>
float Press(std::vector<int>buf, float* Price)
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
std::vector<std::vector<int>> Selection(std::vector<std::vector<int>> Popul, int Oper,float* Price,int count)
{
    std::vector<std::vector<int>> buf;
    bool* way = new bool[Popul.size()];
    int flag = 0;
    for (int i = 0; i < Popul.size(); i++)
    {
        way[i] = false;
    }
    if (Oper == 1)
    {
        while(flag!=count)
        {
            float sum = 0;
            for (int i = 0; i < Popul.size(); i++)
            {
                sum += Press(Popul[i], Price);
            }
            int x = (float)(rand()) / RAND_MAX * sum;
            for (int i = 0; i < Popul.size(); i++)
            {
                x -= Press(Popul[i], Price);
                if (x < 0&&!way[i])
                {
                    buf.push_back(Popul[i]);
                    way[i] = true;
                    flag++;
                    break; 
                }
            }
            
        }
        
    }
    if (Oper == 2)
    {
        while (flag != count)
        {
            int One = rand() % Popul.size();
            int Two = 0;
            do
            {
                Two = rand() % Popul.size();
            } while (One == Two);
            if (Press(Popul[One],Price) < Press(Popul[Two],Price)&&!way[Two])
            {
                buf.push_back(Popul[Two]);
                way[Two] = true;
                flag++;
                
            }
            if(Press(Popul[One], Price) >= Press(Popul[Two], Price) && !way[One])
            {
                buf.push_back(Popul[One]);
                way[One] = true;
                flag++;
            }
            
        }
    }
    return buf;
}
