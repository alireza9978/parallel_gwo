import matplotlib.pyplot as plt
import numpy as np

from GrayWolfOptimizer import gray_wolf_optimizer


def test_function(temp: np.array) -> int:
    return np.sum(np.power(temp, 2))


answer = gray_wolf_optimizer(test_function, -10, 10, 5, 10, 100)

print(answer.convergence[-1])

plt.plot(answer.convergence)
plt.show()
