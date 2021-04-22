#include <omp.h>
#include "gray_wolf_optimizer.cpp"
#include "EvaluationFunctions.cpp"
#include <chrono>
#include <iostream>

using namespace std;

typedef double Fn(double *, int);

int main()
{
    GrayWolf temp;
    omp_set_num_threads(4);
    int dimention = 5000;
    int searchAgentNumber = 20;
    int iteraton = 100;

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
    Solution so = temp.solve(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel algorithm-----------" << endl;
    f = &Eval::rastrigin;
    so = temp.solve_parallel(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel objective-----------" << endl;
    f = &Eval::rastrigin_parallel;
    so = temp.solve(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel both-----------" << endl;
    f = &Eval::rastrigin_parallel;
    so = temp.solve_parallel(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel for algorithm-----------" << endl;
    f = &Eval::rastrigin;
    so = temp.solve_parallel_for(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel for objective-----------" << endl;
    f = &Eval::rastrigin_parallel_for;
    so = temp.solve(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;
    cout << "----------parallel for both-----------" << endl;
    f = &Eval::rastrigin_parallel_for;
    so = temp.solve_parallel_for(f, lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
    so.print();
    cout << endl;    
    
    return 0;
}
