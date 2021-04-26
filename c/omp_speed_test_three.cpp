#include <stdio.h>
#include <chrono>
#include <omp.h>
#include <iostream>
#include <limits>
#include <algorithm> // for std::find
#include <iterator>  // for std::begin, std::end
#include <math.h>
#include <ctime>
#include <string>
#include <list>
#include <stdio.h>
#include <cstring>
#include "EvaluationFunctions.cpp"

// #define search_agents_number 100
// #define dimension 5000

using namespace std;

unsigned long getDateTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

double **one(double *lower_band,
             double *upper_band,
             int search_agents_number = 100,
             int dimension = 10000)
{
    double **positions;
    positions = new double *[search_agents_number];

    for (int j = 0; j < search_agents_number; j++)
    {
        positions[j] = new double[dimension];
        for (int i = 0; i < dimension; i++)
        {
            positions[j][i] = ((rand() / ((double)RAND_MAX)) * (upper_band[i] - lower_band[i]) + lower_band[i]);
        }
    }
    return positions;
}

int main()
{

    srand(time(0));
    omp_set_num_threads(2);
    int search_agents_number = 100;
    int dimension = 10000;
    double upper = 4;
    double lower = -4;
    double upperBand[dimension] = {};
    double lowerBand[dimension] = {};
    for (int i = 0; i < dimension; i++)
    {
        upperBand[i] = upper;
        lowerBand[i] = lower;
    }

    double **positions = one(lowerBand, upperBand, search_agents_number, dimension);

    unsigned long start = getDateTime();
    for (int i = 0; i < search_agents_number; i++)
    {
        Eval::rastrigin(positions[i], dimension);
    }
    cout << "rastrigin" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;

    start = getDateTime();
    for (int i = 0; i < search_agents_number; i++)
    {
        Eval::rastrigin_parallel(positions[i], dimension);
    }
    cout << "rastrigin_parallel" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;

    start = getDateTime();
    for (int i = 0; i < search_agents_number; i++)
    {
        Eval::rastrigin_parallel_for(positions[i], dimension);
    }
    cout << "rastrigin_parallel_for" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;

    return 0;
}
