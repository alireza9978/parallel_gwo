#include "gray_wolf_optimizer.cpp"
#include "EvaluationFunctions.cpp"

using namespace std;

typedef double Fn(double*);

int main()
{   
    GrayWolf temp;
    solution so;
    double upperBand[] = {5, 5, 5, 5, 5};
    double lowerBand[] = {-5, -5, -5, -5, -5};
    
    Fn *f = &Eval::sphere;
    so = temp.solve(f, lowerBand, upperBand, 5, 10, 5, true);
    so.print();
    return 0;
}
