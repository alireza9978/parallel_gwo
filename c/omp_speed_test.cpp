#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;
#define NUM_THREADS 4

unsigned long getDateTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main()
{   
    unsigned long start = getDateTime();
    long num_steps = 100000000;
    double step = 1.0 / (double)num_steps;
    int i, nthreads;
    double pi, sum[NUM_THREADS];
    omp_set_dynamic(0);
    omp_set_num_threads(4);

#pragma omp praallel num_threads(4)
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        cout << id << endl;
        nthrds = omp_get_num_threads();
        cout << nthrds <<endl;
        if (id == 0)
            nthreads = nthrds;
        for (i = id, sum[id] = 0.0; i < num_steps; i += nthreads)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    pi = 0.0;
    for (int i = 0; i < nthreads; i++)
    {
        pi += sum[i] * step;
    }

    cout << pi << endl;
    cout << (getDateTime() - start) << endl;
    return 0;
}
