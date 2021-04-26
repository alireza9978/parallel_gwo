#include <omp.h>
#include <chrono>
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        printf("hello(%d)\n", omp_get_thread_num());
    }
    return 0;

}
