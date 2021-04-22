#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    double bestValue;
    unsigned long startTime;
    unsigned long endTime;
    int dimention;
    double *bestAnswers;

    Solution(int x)
    {
        dimention = x;
        bestAnswers = new double(dimention);
    }

    void print()
    {   
        cout << "best result: " << bestValue << endl;
        cout << "duration: " << (endTime - startTime) << " ms" << endl;
        // for (int i = 0; i < dimention; i++)
        // {
        //     cout << bestAnswers[i] << " ";
        // }
        // cout << endl;
    }
};
