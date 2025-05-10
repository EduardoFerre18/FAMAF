
from random import random, uniform, randint
import math
from timeit import timeit
import numpy as np

'''
a)

Escriba un programa que utilice el algoritmo del adelgazamiento para generar el numero de eventos y
las primeras unidades de tiempo de un proceso de Poisson no homogéneo con función de intensidad

i) 
    λ(t) = 3 + 4 / (t + 1) 0 ≤ t ≤ 3

ii)
    λ(t) = (t - 2)^2 - 5t + 17 0 ≤ t ≤ 5

iii)
    λ(t) = 
        t/2 - 1 si 2 ≤ t ≤ 3
        1 - t/6 si 3 ≤ t ≤ 6
        0 en otro caso

        

b)

Indique una forma de mejorar el algoritmo de adelgazamiento para estos ejemplos usando al menos
3 intervalos.
'''
# a)

def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

def poisson_no_homogeneo_adelgazamiento(T, lamda, lambda_t):
    'Devuelve el número de eventos NT y los tiempos en Eventos'
    'lamda_t(t): intensidad, lamda_t(t)<=lamda'
    'lamda_t es una lista de 3-uplas, de la forma (a, b, fun), donde lamda_t(t) = fun(t) a <= t <= b'
    'lamda debe ser mayor o igual a cualquier valor lamda_t(t)'
    eventos = []
    t = 0
    for l in lambda_t:
        a = l[0]
        b = l[1]
        lambda_func = l[2]
        while (t <= T and a <= t <= b):
            v = random()
            if v <= lambda_func(t)/lamda:
                eventos.append(t)
            t += exponencial(lamda)
    return len(eventos), eventos

print("i):")
# lamda = 7 porque el máximo de λ(t) ocurre en t=0 ==> 3 + 4/(0+1) = 7
print(poisson_no_homogeneo_adelgazamiento(3, 7, [(0, 3, (lambda t: 3 + 4/(t+1)))])) 
print("\n")
print("ii):")
# lamda = 17 porque el máximo de λ(t) ocurre en t=0 ==> (0-2)^2 - 5*0 + 17 = 17
print(poisson_no_homogeneo_adelgazamiento(5, 21, [(0, 5, (lambda t: (t-2)**2 - 5*t +17))]))
print("\n")
print("iii):")
'''
lamda = 1 porque el máximo de λ(t) ocurre en t=3 ==> 
    (3 / 2) - 1 = 0.5
    1 - 3/6 = 0.5
''' 
print(poisson_no_homogeneo_adelgazamiento(6, 1, [(-np.inf, 2, (lambda t: 0)),
                                          (2, 3, (lambda t: (t/2) - 1)),
                                          (3, 6, (lambda t: 1 - (t/6))),
                                          (6, np.inf, (lambda t: 0))]))


# b)

'''
Para mejorar el algoritmo de adelgazamiento, se puede dividir el intervalo en tres partes 
y calcular la intensidad máxima en cada una de ellas. Luego, se puede usar la intensidad máxima de 
cada intervalo para generar eventos en ese intervalo específico. Esto permite reducir el número de eventos 
generados y mejorar la eficiencia del algoritmo.

(i)
I1 = [0, 1]     => λ1 = 7
I2 = [1, 2)     => λ2 = 5
I3 = [2, 3]     => λ3 = 4.9

(ii)
I1 = [0, 2]     => λ1 = 22
I2 = [2, 3)     => λ2 = 7
I3 = [3, 5]     => λ3 = 3

(iii)
I1 = [2, 6]     => λ1 = 0.5
I2 = (-∞, 2)    => λ2 = 1
I3 = [6, ∞)     => λ3 = 1
'''

def poisson_adelgazamiento_mejorado(T, lambda_t, interv):
    'Interv es una lista de 3-uplas (a, b, lambda) tal que para a <= t <= b se verificara si lambda_t(t) <= lambda'
    'lambda_t es una lista de 3-uplas, de la forma (a, b, fun), donde lambda_t(t) = fun(t) a <= t <= b'
    j = 0 #recorre subintervalos.
    eventos = []
    t = 0
    for l in lambda_t:
        a = l[0]
        b = l[1]
        lamda_func = l[2]
        while (t <= T and a <= t <= b):
            a_1 = interv[j][0]
            b_1 = interv[j][1]
            lamda = interv[j][2]
            if a_1 <= t <= b_1:
                v = random()
                if v <= lamda_func(t)/lamda:
                    eventos.append(t)
                t += exponencial(lamda)
            else:
                t = b_1 + (t - b_1) * lamda / interv[j+1][2]
                j += 1
    return len(eventos), eventos