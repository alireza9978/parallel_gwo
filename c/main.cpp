#include <iostream>
#include "gray_wolf_optimizer.h"
#include "solution.h"

int main() {
    solution best = gray_wolf_optimizer::solve();
    std::cout << best.bestValue << std::endl;
    return 0;
}
