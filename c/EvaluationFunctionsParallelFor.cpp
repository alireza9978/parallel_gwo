
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

    double rastrigin(double input[])
    {   // -5 <= xi <= 5
        int n = sizeof(*input) / sizeof(double);
        double result = 10 * n;
        omp_set_num_threads(NUM_THREADS);
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++){
                result += input[i]*input[i] - 10 * cos(2 * PI * input[i]);
            }
        return result;
    }

    double ackley(double input[])
    { // -5 <= xi <= 5
        double x = input[0];
        double y = input[1];
        double power1 = -0.2 * sqrt(0.5 * (x * x + y * y));
        double power2 = 0.5 * (cos(2 * PI * x) + cos(2 * PI * y));
        return -20 * exp(power1) - exp(power2) + E + 20;
    }

    static double sphere(double input[])
    { // -inf <= xi <= inf
        int n = sizeof(*input) / sizeof(double);
        double result = 0;
        omp_set_num_threads(NUM_THREADS);
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++)
                result += input[i] * input[i];
        return result;
    }

    double rosenbrock(double input[])
    { // -inf <= xi <= inf
        int n = sizeof(*input) / sizeof(input[0]);
        double result = 0;
        omp_set_num_threads(NUM_THREADS);
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n - 1; i++)
                result += 100 * pow((input[i + 1] - input[i] * input[i]), 2) + pow((1 - input[i]), 2);
        return result;
    }

    double beale(double input[])
    { // -4.5 <= xi <= 4.5
        double x = input[0];
        double y = input[1];
        return pow((1.5 - x + x * y), 2) + pow((2.25 - x + x * y * y), 2) + pow((2.625 - x + x * y * y * y), 2);
    }

    double goldstin_price(double input[])
    { // -2 <= xi <= 2
        double x = input[0];
        double y = input[1];
        double left_part = 1 + pow(x + y + 1, 2) * (19 - 14 * x + 3 * x * x - 14 * y + 6 * x * y + 3 * y * y);
        double right_part = 30 + pow(2 * x - 3 * y, 2) * (18 - 32 * x + 12 * x * x + 48 * y - 36 * x * y + 27 * y * y);
        return left_part * right_part;
    }

    double booth(double input[])
    { // -10 <= xi <= 10
        double x = input[0];
        double y = input[1];
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    }

    double matyas(double input[])
    { // -10 <= xi <= 10
        double x = input[0];
        double y = input[1];
        return 0.26 * (x * x + y * y) - 0.48 * x * y;
    }

    double himmelblau(double input[])
    { // -5 <= xi <= 5
        double x = input[0];
        double y = input[1];
        return pow((x * x + y - 11), 2) + pow((x + y * y - 7), 2);
    }

    double easom(double input[])
    { // -100 <= xi <= 100
        double x = input[0];
        double y = input[1];
        return -cos(x) * cos(y) * exp(-(pow(x - PI, 2) + pow(y - PI, 2)));
    }

    double coos_in_tray(double input[])
    { // -10 <= xi <= 10
        double x = input[0];
        double y = input[1];
        double value = sin(x) * sin(y) * exp(abs(100 - (sqrt(x * x + y * y) / PI)));
        return -0.0001 * pow(abs(value) + 1, 0.1);
    }

    double eggholder(double input[])
    { // -512 <= xi <= 512
        double x = input[0];
        double y = input[1];
        return -(y + 47) * sin(sqrt(abs(x / 2 + (y + 47)))) - x * sin(sqrt(abs(x - (y + 47))));
    }

    double holder_table(double input[])
    { // -10 <= xi <= 10
        double x = input[0];
        double y = input[1];
        return -abs(sin(x) * cos(y) * exp(abs(1 - sqrt(x * x + y * y) / PI)));
    }

    double mc_cormick(double input[])
    { // -1.5 <= x <= 4    -3 <= y <= 4
        double x = input[0];
        double y = input[1];
        return sin(x + y) + pow(x - y, 2) - 1.5 * x + 2.5 * y + 1;
    }

    double schaffer(double input[])
    { // -100 <= xi <= 100
        double x = input[0];
        double y = input[1];
        return 0.5 + (pow(sin(x * x - y * y), 2) - 0.5) / pow(1 + 0.0001 * (x * x + y * y), 2);
    }

    double schaffer2(double input[])
    { // -100 <= xi <= 100
        double x = input[0];
        double y = input[1];
        return 0.5 + (pow(cos(sin(abs(x * x - y * y))), 2) - 0.5) / pow(1 + 0.0001 * (x * x + y * y), 2);
    }

    double styblinski(double input[])
    {   // -5 <= xi <= 5
        int n = sizeof(*input) / sizeof(double);
        double result = 0;
        omp_set_num_threads(NUM_THREADS);
        #pragma omp parallel for reduction (+:result)
            for (int i = 0; i < n; i++){
                result += pow(input[i], 4) - 16 * pow(input[i], 2) + 5 * input[i];
            }
        result /= 2;
        return result;
    }
};