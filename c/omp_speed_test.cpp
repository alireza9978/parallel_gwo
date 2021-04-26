#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;
#define NUM_THREADS 4
static long num_steps = 400000000;
double step;

unsigned long getDateTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void normal()
{
    unsigned long start = getDateTime();

    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    cout << "normal" << endl;
    cout << pi << endl;
    cout << (getDateTime() - start) << endl;
}

void parallel()
{
    unsigned long start = getDateTime();

    int nthreads;
    double pi, main_sum[NUM_THREADS];

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum = 0.0;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0)
            nthreads = nthrds;
        for (i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        main_sum[id] = sum;
    }
    pi = 0.0;
    for (int i = 0; i < nthreads; i++)
    {
        pi += main_sum[i] * step;
    }

    cout << "parallel" << endl;
    cout << pi << endl;
    cout << (getDateTime() - start) << endl;
}

void parallel_for()
{
    unsigned long start = getDateTime();
    step = 1.0 / (double)num_steps;
    int i, nthreads;
    double pi = 0.0;
    // double x;
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for reduction(+:pi)
    for (i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }

    pi = pi * step;
    cout << "parallel_for" << endl;
    cout << pi << endl;
    cout << (getDateTime() - start) << endl;
}

int main()
{
    parallel_for();

    parallel();

    normal();

    return 0;
}
