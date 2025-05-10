from random import random, uniform
import math
from timeit import timeit

'''
f(x) = 1/x si 1 <= x <= e, 0 en otro caso

'''

# Desarrolle dos métodos para generar una variable aleatoria X Aplicando Transformada inversa y el método de aceptación y rechazo con una variable uniforme.

# 1) Transformada inversa
def t_inv():
    U = random()
    return math.exp(U)

# 2) Aceptación-rechazo
def a_r():
    while True:
        U = random()
        y = uniform(1, math.exp(1))
        if U < 1/y:
            return y
        
# b)Compare la eficiencia de ambos métodos realizando 10.000 simulaciones y comparando el promedio de los valores obtenidos. Compruebe que se obtiene un valor aproximado del valor esperado de X.

def esperanza(fun, Nsims=10000):
    sum = 0
    for _ in range(Nsims):
        sum += fun()
    return (sum/Nsims)

print(f"E[X] estimado con 10000 simulaciones y usando el método de la transformada inversa = {esperanza(t_inv)}")
print(f"E[X] estimado con 10000 simulaciones y usando el método de aceptación-rechazo = {esperanza(a_r)}")
print(f"E[X] real calculado = {math.e - 1}")


tiempo_tinv = timeit('t_inv()', globals=globals(), number=10000)
tiempo_ayr = timeit('a_r()', globals=globals(), number=10000)
print(f"Tiempo de ejecución del método de la transformada inversa: {tiempo_tinv:.5f} segundos")
print(f"Tiempo de ejecución del método de aceptación-rechazo: {tiempo_ayr:.5f} segundos")

# c) Estime la probabilidad P(X ≤ 2) y compárela con el valor real.
def prob_2(fun, Nsims=10000):
    count = 0
    for _ in range(Nsims):
        if fun() <= 2:
            count += 1
    return count/Nsims

print(f"P(X <= 2) estimado con 10000 simulaciones y usando el método de la transformada inversa = {prob_2(t_inv)}")
print(f"P(X <= 2) estimado con 10000 simulaciones y usando el método de aceptación-rechazo = {prob_2(a_r)}")
print(f"P(X <= 2) real calculado = {'%.3f'%math.log(2)}")