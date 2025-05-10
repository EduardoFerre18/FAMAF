from random import random
import math

# X es una lista de variables aleatorias, y P es una lista de probabilidades que deben sumar 1
def comp(X, P):
    F = []
    for i in range(len(P)):
        ind = slice(0, i+1)
        F.append(round(sum(P[ind]), 2))
    U = random()
    i = 0
    while U >= F[i]:
        i += 1
    return X[i]


def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

def esperanza(Nsims=10000):
    sum = 0
    P = [0.5, 0.3, 0.2]
    for _ in range(Nsims):
        X = [exponencial(1/3), exponencial(1/5), exponencial(1/7)]
        sum += comp(X, P)
    return (sum/Nsims)

print(f"E[X] estimado con 10000 simulaciones = {esperanza()}")
print(f"E[X] real calculado = 4.4")