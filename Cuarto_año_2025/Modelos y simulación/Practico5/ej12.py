from random import random, uniform
import math
from timeit import timeit

'''
Escriba un programa que calcule el número de eventos y sus tiempos de arribo en las primeras
T unidades de tiempo de un proceso de Poisson homogéneo con parámetro λ.

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