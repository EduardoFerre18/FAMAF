import numpy as np
import math 
import random


def integral_ab(funciong, a, b, d, Nsim):
    media = funciong(a + (b-a) * random.random()) * (b-a)
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        x = funciong(a + (b-a) * random.random()) * (b-a)
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return media


def integral_0inf(funciong, d, Nsim):
    y = random.random()
    media = (1 / y ** 2) * funciong(((1/y) - 1))
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        y = random.random()
        x = (1 / y ** 2) * funciong(((1/y) - 1))
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return media


def integral_ninf0(funciong, d, Nsim):
    y = random.random()
    media = (1 / y ** 2)*funciong(-(1/(y)) + 1)
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        y = random.random()
        x = (1 / y ** 2)*funciong(-(1/(y)) + 1)
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return media

def IntegralMonteCarlo(funciong, a, b, d, Nsim):
    if a != -np.inf and b != np.inf:
        result = integral_ab(funciong, a, b, d, Nsim)
    elif b == np.inf and a != -np.inf:
        if a == 0:
            result = integral_0inf(funciong, d, Nsim)
        else:
            result1 = IntegralMonteCarlo(funciong, 0, b, d, Nsim)
            result2 = IntegralMonteCarlo(funciong, a, 0, d, Nsim)
            result = result1 + result2
    elif b != np.inf and a == -np.inf:
        if b == 0:
            result = integral_ninf0(funciong, d, Nsim)
        else:
            result1 = IntegralMonteCarlo(funciong, 0, b, d, Nsim)
            result2 = IntegralMonteCarlo(funciong, a, 0, d, Nsim)
            result = result1 + result2
    elif a == -np.inf and b == np.inf:
        result1 = IntegralMonteCarlo(funciong, 0, b, d, Nsim)
        result2 = IntegralMonteCarlo(funciong, a, 0, d, Nsim)
        result = result1 + result2
    return result

def f_i(x):
    return math.exp(x) / math.sqrt(2 * x)

def f_ii(x):
    return (x ** 2) * math.exp(-x ** 2)

result_i = IntegralMonteCarlo(f_i, 0, 1, 0.01, 100)
result_ii = IntegralMonteCarlo(f_ii, -np.inf, np.inf, 0.01, 100)
print("Valor real de la integral i:", 2.0685)
print("La estimación para i) generando al menos 100 valores y y deteniendose cuando la desviación estándar muestral del estimador es menor a 0.01:", '%.3f'%result_i)
print("Valor real de la integral ii:", 0.886)
print("La estimación para ii) generando al menos 100 valores y y deteniendose cuando la desviación estándar muestral del estimador es menor a 0.01:", '%.3f'%result_ii)