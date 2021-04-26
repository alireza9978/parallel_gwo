#include <omp.h>
#include "gray_wolf_optimizer_two.cpp"
#include <chrono>
#include <iostream>

using namespace std;

typedef double Fn(double *, int);

int main()
{
    GrayWolfTwo temp_two;
    omp_set_num_threads(2);
    int dimention = 10000;
    int searchAgentNumber = 100;
    int iteraton = 10;

    double upper = 4;
    double lower = -4;
    double upperBand[dimention] = {};
    double lowerBand[dimention] = {};
    for (int i = 0; i < dimention; i++)
    {
        upperBand[i] = upper;
        lowerBand[i] = lower;
    }

    cout << "----------normal-----------" << endl;
    Fn *f = &Eval::rastrigin;
    Solution so = temp_two.solve(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel_for_objective-----------" << endl;
    so = temp_two.solve_normal_parallel_for_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel_objective-----------" << endl;
    so = temp_two.solve_normal_parallel_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;    
    
    return 0;
}
