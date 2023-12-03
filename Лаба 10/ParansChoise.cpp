#include "ParansChoise.h"
#include <iostream>
#include<vector>
float Pres(std::vector<int>buf, float* Price)
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
int* Parans(std::vector<std::vector<int>> Popul, int Oper,float*Price)
{
    int* arr = new int[2];
    arr[0] = 0;
    arr[1] = 0;
    if (Oper == 1)
    {
        arr[0] = rand() % Popul.size();
        do 
        {
            arr[1] = rand() % Popul.size();
        } while (arr[0] == arr[1]);
        
        return arr;
    }
    if (Oper == 2)
    {
        float sum = 0;
        for (int i = 0; i < Popul.size(); i++)
        {
            sum += Pres(Popul[i],Price);
        }

        for (int j = 0; j < 2; j++)
        {
            float x = (float)(rand()) / RAND_MAX * sum;
            for (int i = 0; i < Popul.size(); i++)
            {
                x -= Pres(Popul[i],Price);
                if (x <= 0)
                {
                    if (arr[0]==i&&j==1)//проверяю вдруг второй родитлей совпал с первым
                    {
                        if (i == 0)
                        {
                            arr[1] = i + 1;
                            break;
                        }
                        else
                        {
                            arr[1] = i - 1;
                            break;
                        }
                    }
                    arr[j] = i;
                    break;
                }
            }
        }
        return arr;
    }
    
}
