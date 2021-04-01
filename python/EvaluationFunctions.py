import math
import numpy as np


def ackley(input):  # -5 <= xi <= 5
    x = input[0]
    y = input[1]
    power1 = -0.2*math.sqrt(0.5 * (x**2 + y**2))
    power2 = 0.5*(math.cos(2*math.pi*x) + math.cos(2*math.pi*y))
    return -20*math.exp(power1) - math.exp(power2) + math.e + 20


def sphere(input):  # -inf <= xi <= inf
    return np.sum(np.power(input, 2))


def rosenbrock(input):  # -inf <= xi <= inf
    n = len(input)
    result = 0
    for i in range(n-1):
        result += 100*(input[i+1]-input[i]**2)**2 + (1-input[i])**2
    return result


def beale(input):   # -4.5 <= xi <= 4.5
    x = input[0]
    y = input[1]
    return (1.5-x+x*y)**2 + (2.25-x+x*y**2)**2 + (2.625 - x + x*y**3)**2


def goldstin_price(input):  # -2 <= xi <= 2
    x = input[0]
    y = input[1]
    left_part = 1 + (x+y+1)**2*(19-14*x+3*x**2-14*y+6*x*y+3*y**2)
    right_part = 30 + (2*x-3*y)**2*(18-32*x+12*x**2+48*y-36*x*y+27*y**2)
    return left_part*right_part


def booth(input):   # -10 <= xi <= 10
    x = input[0]
    y = input[1]
    return (x + 2*y - 7)**2 + (2*x + y  - 5)**2


def matyas(input):  # -10 <= xi <= 10
    x = input[0]
    y = input[1]
    return 0.26 * (x**2+y**2)-0.48*x*y


def himmelblau(input):  # -5 <= xi <= 5
    x = input[0]
    y = input[1]
    return (x**2+y-11)**2+(x+y**2-7)**2


def easom(input):   # -100 <= xi <= 100
    x = input[0]
    y = input[1]
    return -math.cos(x)*math.cos(y)*math.exp(-((x-math.pi)**+(y-math.pi)**2)))


def coos_in_tray(input):
    x = input[0]
    y = input[1]
    value = math.sin(x)*math.sin(y)*math.exp(abs(100-(math.sqrt(x**2+y**2)/math.pi)))
    return -0.0001*(abs(value)+1)**0.1


def eggholder(input):
    x = input[0]
    y = input[1]
    return -(y+47)*math.sin(math.sqrt(abs(x/2+(y+47)))) - x*math.sin(math.sqrt(abs(x-(y+47))))


def holder_table(input):
    x = input[0]
    y = input[1]
    return -abs(math.sin(x)*math.cos(y)*math.exp(abs(1-math.sqrt(x**2+y**2)/math.pi)))


def mc_cormick(input):
    x = input[0]
    y = input[1]
    return math.sin(x+y)+(x-y)**2-1.5*x+2.5*y+1


def schaffer(input):
    x = input[0]
    y = input[1]
    return 0.5 + (math.sin(x**2-y**2)**2-0.5)/(1+0.0001*(x**2+y**2))**2


def schaffer2(input):
    x = input[0]
    y = input[1]
    return 0.5 + (math.cos(math.sin(abs(x**2-y**2)))**2 - 0.5) / (1+0.0001*(x**2+y**2))**2



