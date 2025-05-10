from random import random
import math
from timeit import timeit

# F(X) = x^n, 0 <= x <= 1

# Productoria

def prod(n):
    X = []
    for _ in range(n):
        U = random()
        X.append(U)
    return max(X)

# Transformada inversa

def t_inv(n):
    U = random()
    return U**(1/n)


# Aceptación rechazo

def a_r(n):
    while True:
        U = random()
        y = random()
        if U < y**(n-1):
            return y
        

# b) Analice la eficiencia de los tres métodos para generar la variable a partir de F.

# Primero vamos a verificar que los métodos generan la variable aleatoria correctamente.

def esperanza(fun, n, Nsims=10000):
    sum = 0
    for _ in range(Nsims):
        sum += fun(n)
    return (sum/Nsims)

print(f"E[X] estimado con 10000 simulaciones y n=10, usando el método de la productoria = {esperanza(prod, 10)}")
print(f"E[X] estimado con 10000 simulaciones y n=10, usando el método de la transformada inversa = {esperanza(t_inv, 10)}")
print(f"E[X] estimado con 10000 simulaciones y n=10, usando el método de aceptación-rechazo = {esperanza(a_r, 10)}")
print(f"E[X] real calculado = {10/11}")
print("\n")

# Ahora vamos a comparar los tiempos de ejecución de cada método 

tiempo_prod = timeit('prod(10)', globals=globals(), number=10000)
tiempo_tinv = timeit('t_inv(10)', globals=globals(), number=10000)
tiempo_ayr = timeit('a_r(10)', globals=globals(), number=10000)

print(f"Tiempo de ejecución del método de la productoria: {tiempo_prod:.5f} segundos")
print(f"Tiempo de ejecución del método de la transformada inversa: {tiempo_tinv:.5f} segundos")
print(f"Tiempo de ejecución del método de aceptación-rechazo: {tiempo_ayr:.5f} segundos")
print("\n")
