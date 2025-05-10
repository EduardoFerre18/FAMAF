import math
import random

# Ejercicio 1

def f(x) :
    return math.sqrt(x + math.sqrt(x))

# Aclaración: Se define la función solo para los limtes a=1 y b = 7

def monte_carlo(N):
    Integral = 0
    for _ in range(N):
        Integral += f(1 + (6 * random.random()))
    return Integral * 6 / N 

print("Resultados del ejercicio 1: ")
for N in [1000, 10000, 100000]: 
    print(f"Monte Carlo con {N} simulaciones: {monte_carlo(N):.6f}")
print("\n")

# Ejercicio 2

def juego():
    suma = 0
    cont = 0
    while suma <= 1:
        suma += random.random()
        cont += 1
    return cont % 2 == 1

def pares(N):
    aciertos = 0
    for _ in range(N):
        if juego():
            aciertos += 1
    return aciertos / N

print("Resultados del ejercicio 2:")
for i in [100, 1000, 10000]:
    print(f"Probabilidad de que el número total de sumandos sea impar con {i} simulaciones: {pares(i)}")