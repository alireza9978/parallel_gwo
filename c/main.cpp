#include "gray_wolf_optimizer.cpp"
#include "EvaluationFunctions.cpp"

using namespace std;

typedef double Fn(double*);

int main()
{   
    GrayWolf temp;
    
    double upperBand[] = {50, 50, 50, 50, 50};
    double lowerBand[] = {-50, -50, -50, -50, -50};
    
    Fn *f = &Eval::sphere;
    Solution so = temp.solve(f, lowerBand, upperBand, 5, 10, 10, true);
    so.print();
    return 0;
}
