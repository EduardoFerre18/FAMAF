import math 
from scipy.stats import chi2
import numpy as np
import random

def t_ej6(N, P):
    T = 0
    for i in range(1, len(N)):
        T += (N[i] - sum(N)*P[i]) ** 2 / (sum(N)*P[i])
    return T

N = [0, 188, 138, 87, 65, 48, 32, 30, 34, 13, 2]
P = [0, 0.31, 0.22, 0.12, 0.10, 0.08, 0.06, 0.04, 0.04, 0.02, 0.01]
t0 = t_ej6(N, P)

print("Valor del estadístico T:", t0)
print("Valor de p-valor usando chi^2:", chi2.sf(t0, 9))

def generar_tiro():
    F = [0.0, 0.31, 0.53, 0.65, 0.75, 0.83, 0.89, 0.93, 0.97, 0.99, 1]
    U = random.random()
    i = 0
    while U > F[i]:
        i += 1
    return i

def sim_rueda(P, t0, Nsims=1000):
    pvalor = 0
    for _ in range(Nsims):
        muestra = []
        frec = [0 for i in range(11)]
        for i in range(637):
            x = generar_tiro()
            muestra.append(x)
            frec[x] += 1
        T_est = 0
        for i in range(1, len(N)):
            T_est += (frec[i] - len(muestra)*P[i])**2 / (len(muestra)*P[i])
        if T_est > t0:
            pvalor += 1
    return pvalor/Nsims
    
print("Valor de p-valor estimado generando las frecuencias:", sim_rueda(P, t0))   