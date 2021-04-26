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

    unsigned long noraml_mean_time = 0, paralllel_for_objective_mean_time = 0, parallel_for_algorithm_mean_time = 0,
                  prallel_for_both_mean_time = 0, parallel_objective_mean_time = 0, parallel_algorithm_mean_time = 0,
                  parallel_both_mean_time = 0;
    for (int i = 0; i < repeat_algorithm_count; i++)
    {

        Solution so = temp_two.solve(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        noraml_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_normal_parallel_for_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        paralllel_for_objective_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_normal_parallel_objective(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        parallel_objective_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_parallel(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        parallel_algorithm_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_parallel_both(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        parallel_both_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_parallel_for(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        parallel_for_algorithm_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;

        so = temp_two.solve_parallel_for_both(lowerBand, upperBand, dimention, searchAgentNumber, iteraton, false);
        prallel_for_both_mean_time += (so.endTime - so.startTime) / repeat_algorithm_count;
    }
    printf("noraml_mean_time : %ld ms \nparalllel_for_objective_mean_time : %ld ms \nparallel_for_algorithm_mean_time : %ld ms \nprallel_for_both_mean_time : %ld ms \nparallel_objective_mean_time : %ld ms \nparallel_algorithm_mean_time : %ld ms \nparallel_both_mean_time : %ld ms \n",
           noraml_mean_time, paralllel_for_objective_mean_time, parallel_for_algorithm_mean_time,
           prallel_for_both_mean_time, parallel_objective_mean_time, parallel_algorithm_mean_time,
           parallel_both_mean_time);

    return 0;
}
