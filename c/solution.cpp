#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    float bestValue;
    string startTime;
    string endTime;
    int dimention;
    double *bestAnswers;

    Solution(int x)
    {
        dimention = x;
        bestAnswers = new double(dimention);
    }

    void print()
    {   
        cout << "result" << endl;
        cout << startTime << endl;
        cout << bestValue << endl;
        cout << endTime << endl;
        for (int i = 0; i < dimention; i++)
        {
            cout << bestAnswers[i] << " ";
        }
        cout << endl;
    }
};
