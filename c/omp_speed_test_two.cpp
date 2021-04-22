#include <omp.h>
#include <stdio.h>


int main()
{   
    omp_set_dynamic(0);  
    omp_set_num_threads(4);
#pragma omp parallel num_threads(4)
    {   
        printf("hello(%d)\n", omp_get_thread_num());
    }
    
    return 0;
}
