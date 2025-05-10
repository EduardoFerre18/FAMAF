from random import random, uniform
import math
from timeit import timeit

'''
Una variable aleatoria X tiene distribución de Cauchy con parámetro λ > 0 si su densidad es:
f(x) = 1/(πλ(1+(x/λ)^2)), x ∈ R

a) Implemente el método de razón entre uniformes para simular X con parámetro λ = 
 Desarrolle un algoritmo CAUCHY( ) que genere pares (U,V) con distribución uniforme en C_f
,y
devuelva X = V/U. Entonces X tiene la distribución deseada

b) ) Pruebe que si X tiene distribución de Cauchy con parámetro 1, entonces λX tiene distribución de
Cauchy con parámetro λ

c) Utilice esta propiedad para modificar el algoritmo anterior, e implementar CAUCHY(LAMDA) que
simule una variable X con distribución de Cauchy de parámetro λ.

d) Realice 10.000 simulaciones y calcule la proporción de veces que el resultado cae en el intervalo
(−λ,λ), para λ = 1, λ = 2.5 y λ = 0.3. Compare con la probabilidad teórica.


'''

#a) 

def cauchy():
    while True:
        U = random()
        V = uniform(-1, 1)
        if U ** 2 + V ** 2 < 1 :
            return V / U

#b) 

def cauchy(lamda):
    while 1:
        u = random()
        v = uniform(-1, 1)
        if u**2 + v**2 < 1:
            return lamda * v/u
        

#d)

def prob(lamda, Nsims=10000):
    count = 0
    for _ in range(Nsims):
        x = cauchy(lamda)
        if x <= lamda and x >= -lamda:
            count += 1
    return count/Nsims

print(f"P(-1 <= X <= 1) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob(1)}")
print(f"P(-2.5 <= X <= 2.5) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob(2.5)}")
print(f"P(-0.3 <= X <= 0.3) estimado con 10000 simulaciones y usando el método de la razón entre uniformes = {prob(0.3)}")
print(f"Probabilidad de que X este en el intervalo (−λ,λ) para cualquier λ = {1/2}")
