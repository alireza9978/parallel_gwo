
#include <math.h>
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

#define PI 3.14159265
#define E 2.71828182845904523536

#define NUM_THREADS 4

class Eval
{
public:

    static double rastrigin(double input[], int n)
    {   // -5 <= xi <= 5
        double result = 10 * n;
        #pragma omp parallel
        {
            int id, nthrds;
            double sum = 0;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            for (int i = id; i < n; i+=nthrds){
                sum += input[i]*input[i] - 10 * cos(2 * PI * input[i]);
            }
            #pragma atomic
                result += sum;
        }
        return result;
    }

    static double sphere(double input[], int n)
    { // -inf <= xi <= inf
        double result = 0;
        #pragma omp parallel
        {
            int id, nthrds;
            double sum = 0;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            for (int i = id; i < n; i+=nthrds)
                sum += input[i] * input[i];
            #pragma atomic
                result += sum;
        }
        return result;
    }

    static double rosenbrock(double input[], int n)
    { // -inf <= xi <= inf
        double result = 0;
        #pragma omp parallel
        {
            int id, nthrds;
            double sum = 0;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            for (int i = id; i < n - 1; i+=nthrds)
                sum += 100 * pow((input[i + 1] - input[i] * input[i]), 2) + pow((1 - input[i]), 2);
            #pragma atomic
                result += sum;
        }
        return result;
    }

    static double styblinski(double input[], int n)
    {   // -5 <= xi <= 5
        double result = 0;
        #pragma omp parallel
        {
            int id, nthrds;
            double sum = 0;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            for (int i = id; i < n - 1; i+=nthrds)
                sum += pow(input[i], 4) - 16 * pow(input[i], 2) + 5 * input[i];
            #pragma atomic
                result += sum;
        }
        result /= 2;
        return result;
    }
};