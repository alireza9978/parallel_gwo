#include <chrono>
#include <omp.h>
#include <iostream>

using namespace std;

unsigned long getDateTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

double **two(double *lower_band,
             double *upper_band,
             int search_agents_number = 100,
             int dimension = 10000)
{
    unsigned long start = getDateTime();
    double **positions = new double *[search_agents_number];
#pragma omp parallel
    {
        srand(time(0));
        int id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        int a = search_agents_number;
        int b = dimension;
        for (int j = 0; j < a; j++)
        {
            positions[j] = new double[b];
            for (int i = id; i < b; i += nthrds)
            {
                positions[j][i] = ((rand() / (double)RAND_MAX) * (upper_band[i] - lower_band[i]) + lower_band[i]);
            }
        }
    }
    cout << "two" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;
    return positions;
}

double **one(double *lower_band,
             double *upper_band,
             int search_agents_number = 100,
             int dimension = 10000)
{
    srand(time(0));
    unsigned long start = getDateTime();
    double **positions = new double *[search_agents_number];
    for (int j = 0; j < search_agents_number; j++)
    {
        positions[j] = new double[dimension];
        for (int i = 0; i < dimension; i++)
        {
            positions[j][i] = ((rand() / ((double)RAND_MAX)) * (upper_band[i] - lower_band[i]) + lower_band[i]);
        }
    }
    cout << "one" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;
    return positions;
}

double **three(double *lower_band,
               double *upper_band,
               int search_agents_number = 100,
               int dimension = 10000)
{
    unsigned long start = getDateTime();
    double **positions = new double *[search_agents_number];
#pragma omp parallel
    {
        srand(time(0));
#pragma omp for
        for (int j = 0; j < search_agents_number; j++)
        {
            positions[j] = new double[dimension];
            for (int i = 0; i < dimension; i++)
            {
                positions[j][i] = ((rand() / ((double)RAND_MAX)) * (upper_band[i] - lower_band[i]) + lower_band[i]);
            }
        }
    }
    cout << "three" << endl;
    cout << (getDateTime() - start) << endl;
    cout << endl;
    return positions;
}

int main()
{

    omp_set_num_threads(2);
    int search_agents_number = 1000;
    int dimension = 1000;
    double upper = 4;
    double lower = -4;
    double *upperBand = new double[dimension];
    double *lowerBand = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        upperBand[i] = upper;
        lowerBand[i] = lower;
    }

    double **positions;
    positions = three(lowerBand, upperBand, search_agents_number, dimension);
    positions = one(lowerBand, upperBand, search_agents_number, dimension);
    positions = two(lowerBand, upperBand, search_agents_number, dimension);

    return 0;
}
