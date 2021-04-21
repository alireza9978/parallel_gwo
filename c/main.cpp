#include <omp.h>
#include "gray_wolf_optimizer.cpp"
#include "EvaluationFunctions.cpp"
// #include "EvaluationFunctionsParallelFor.cpp"
// #include "EvaluationFunctionsParallel.cpp"


using namespace std;

typedef double Fn(double *, int);

int main()
{
    GrayWolf temp;
    omp_set_num_threads(4);
    
    int dimention = 50000;

    double upper = 5;
    double lower = -5;
    double upperBand[dimention] = {};
    double lowerBand[dimention] = {};
    for (int i = 0; i < dimention; i++)
    {
        upperBand[i] = upper;
        lowerBand[i] = lower;
    }

    Fn *f = &Eval::rastrigin;
    Solution so = temp.solve(f, lowerBand, upperBand, dimention, 10, 50, true);
    so.print();
    return 0;
}
