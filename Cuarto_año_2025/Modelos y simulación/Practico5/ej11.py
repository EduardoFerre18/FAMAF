from random import random, uniform
import math
from timeit import timeit


'''
Sea X una variable aleatoria con distribución de Cauchy de parámetro λ.

b) Simule X aplicando el método de transformada inversa.

d) Realice 10000 simulaciones y calcular la proporción de veces que el resultado cae en el intervalo
(−λ,λ), para λ = 1, λ = 2.5 y λ = 0.3. Compare con la probabilidad teórica.

e) Compare la eficiencia de este algoritmo con el método de razón entre uniformes


'''

#b) 

def cauchy_ti(lamda):
    U = random()
    return lamda * math.tan(math.pi * U - math.pi/2)

#d)

def prob_ti(lamda, Nsims=10000):
    count = 0
    for _ in range(Nsims):
        x = cauchy_ti(lamda)
        if x <= lamda and x >= -lamda:
            count += 1
    return count/Nsims

print(f"P(-1 <= X <= 1) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob_ti(1)}")
print(f"P(-2.5 <= X <= 2.5) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob_ti(2.5)}")
print(f"P(-0.3 <= X <= 0.3) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob_ti(0.3)}")
print(f"Probabilidad de que X este en el intervalo (−λ,λ) para cualquier λ = {1/2}")
print("\n")

#e) 

def cauchy(lamda):
    while 1:
        u = random()
        v = uniform(-1, 1)
        if u**2 + v**2 < 1:
            return lamda * v/u
    
tiempo_tinv = timeit('cauchy_ti(1)', globals=globals(), number=10000)
tiempo_ayr = timeit('cauchy(1)', globals=globals(), number=10000)
print(f"Tiempo de ejecución del método de la transformada inversa: {tiempo_tinv:.5f} segundos")
print(f"Tiempo de ejecución del método de aceptación-rechazo: {tiempo_ayr:.5f} segundos")