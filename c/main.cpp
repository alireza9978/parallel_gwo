#include <omp.h>
#include "gray_wolf_optimizer_two.cpp"
#include <chrono>
#include <iostream>

using namespace std;

typedef double Fn(double *, int);

int main()
{   
    int repeat_algorithm_count = 10;
    GrayWolfTwo temp_two;
    omp_set_num_threads(8);
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

    unsigned long noraml_mean_time = 0, paralllel_for_objective_mean_time = 0, parallel_for_algorithm_mean_time = 0,
     prallel_for_both_mean_time = 0, parallel_objective_mean_time = 0, parallel_algorithm_mean_time = 0,
     parallel_both_mean_time = 0;
    for (int i=0; i<repeat_algorithm_count; i++){
        cout << "----------normal-----------" << endl;
        Fn *f = &Eval::rastrigin;
        Solution so = temp_two.solve(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        so.print();
        noraml_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;
        cout << endl;
        cout << "----------parallel_for_objective-----------" << endl;
        so = temp_two.solve_normal_parallel_for_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        so.print();
        paralllel_for_objective_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;
        cout << endl;
        cout << "----------parallel_objective-----------" << endl;
        so = temp_two.solve_normal_parallel_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        so.print();
        parallel_objective_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;
        cout << endl;    
    }
    printf("normal_mean_time : %d ms \nparallel_for_objective_mean_time : %d ms \n
    parallel_objective_mean_time : %d ms \n",
    noraml_mean_time, paralllel_for_objective_mean_time, parallel_objective_mean_time);
    return 0;
}
