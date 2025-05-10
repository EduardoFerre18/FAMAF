from random import random
import math 

def M(X):
    return max(X)

def m(X):
    return min(X)

def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

x_M = []
x_m = []

for _ in range(10):
    x_M.append(M([exponencial(1), exponencial(2), exponencial(3)]))
    x_m.append(m([exponencial(1), exponencial(2), exponencial(3)]))

print("Muestra de F_M: ", x_M)
print("\n")
print("Muestra de F_m: ", x_m)