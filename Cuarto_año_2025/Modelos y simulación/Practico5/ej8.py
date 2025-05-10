from random import random, uniform
import math
from timeit import timeit

'''
b) 
U y V son variables aleatorias uniformes en (0,1)
X = U + V

f(x) = 
    x si 0 <= x < 1
    2-x si 1 <= x < 2
    0 en otro caso

Desarrolle tres algoritmos que simulen la variable X:
i) Usando la propiedad que X es suma de dos uniformes.
ii) Aplicando transformada inversa.
iii) Con el método de rechazo
'''

#i)

def suma_uniformes():
    U = random()
    V = random()
    return U + V

# ii) Transformada inversa
def t_inv():
    U = random()
    if U < 1/2:
        return math.sqrt(2*U)
    else:
        return 2 - math.sqrt(2*(1-U))
    
# iii) Aceptación-rechazo

def a_r():
    while True: 
        Y = uniform(0, 2)
        U = random()
        if Y < 1 and U < Y:
            return Y 
        elif 1 <= Y < 2 and U < (2-Y):
            return Y
        
'''
c) Compare la eficiencia de los tres algoritmos. Para cada caso, estimar el valor esperado promediando
10.000 valores simulados, ¿Para qué valor x0 se cumple que P(X > x0) = 0.125?
'''

def esperanza(fun, Nsims=10000):
    sum = 0
    for _ in range(Nsims):
        sum += fun()
    return (sum/Nsims)

print(f"E[X] estimado con 10000 simulaciones y usando el método de la suma de uniformes = {esperanza(suma_uniformes)}")
print(f"E[X] estimado con 10000 simulaciones y usando el método de la transformada inversa = {esperanza(t_inv)}")
print(f"E[X] estimado con 10000 simulaciones y usando el método de aceptación-rechazo = {esperanza(a_r)}")
print(f"E[X] real calculado = 1")
print("\n")

# d) Compare la proporción de veces que el algoritmo devuelve un número mayor que x0 con esta probabilidad

def prob_x0(fun, x0, Nsims=10000):
    count = 0
    for _ in range(Nsims):
        if fun() > x0:
            count += 1
    return count/Nsims

x0 = 1.5
print(f"P(X > {x0}) estimado con 10000 simulaciones y usando el método de la suma de uniformes = {prob_x0(suma_uniformes, x0)}")
print(f"P(X > {x0}) estimado con 10000 simulaciones y usando el método de la transformada inversa = {prob_x0(t_inv, x0)}")
print(f"P(X > {x0}) estimado con 10000 simulaciones y usando el método de aceptación-rechazo = {prob_x0(a_r, x0)}")
print(f"P(X > {x0}) real calculado = 0.125")
print("\n")
