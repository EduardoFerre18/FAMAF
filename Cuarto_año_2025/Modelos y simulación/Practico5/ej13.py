from random import random, uniform, randint
import math
from timeit import timeit

'''

Los autobuses que llevan los aficionados a un encuentro deportivo llegan a destino de acuerdo
con un proceso de Poisson a razón de cinco por hora. La capacidad de los autobuses es una variable
aleatoria que toma valores en el conjunto: {20,21,...,40} con igual probabilidad. A su vez, las capacidades
de dos autobuses distintos son variables independientes. Escriba un algoritmo para simular la llegada de
aficionados al encuentro en el instante t = 1hora.

'''

def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

def eventos_poisson(lamda, T):
    t = exponencial(lamda)
    eventos = []
    while t <= T:
        eventos.append(t)
        t += exponencial(lamda)
    return len(eventos), eventos

def llegada_aficionados():
    tiempos = eventos_poisson(5, 1)[1]
    aficionados = []
    for tiempo in tiempos:
        aficionados.append(randint(20, 40))
    return aficionados, tiempos

