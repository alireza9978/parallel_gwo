
#include <math.h>
#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

#define PI 3.14159265
#define E 2.71828182845904523536

class Eval
{
public:

    static double rastrigin(double input[], int n)
    {   // -5 <= xi <= 5
        double result = 10 * n;
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++){
                result += input[i]*input[i] - 10 * cos(2 * PI * input[i]);
            }
        return result;
    }

    static double sphere(double input[], int n)
    { // -inf <= xi <= inf
        double result = 0;
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++)
                result += input[i] * input[i];
        return result;
    }

    static double rosenbrock(double input[],int n)
    { // -inf <= xi <= inf
        double result = 0;
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n - 1; i++)
                result += 100 * pow((input[i + 1] - input[i] * input[i]), 2) + pow((1 - input[i]), 2);
        return result;
    }

    static double styblinski(double input[], int n)
    {   // -5 <= xi <= 5
        double result = 0;
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++){
                result += pow(input[i], 4) - 16 * pow(input[i], 2) + 5 * input[i];
            }
        result /= 2;
        return result;
    }
};