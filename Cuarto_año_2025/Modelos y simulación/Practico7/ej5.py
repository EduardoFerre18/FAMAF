import math 
from scipy.stats import chi2
import numpy as np

M = [6, 7, 3, 4, 7, 3, 7, 2, 6, 3, 7, 8, 2, 1, 3, 5, 8, 7]
media_muestral = sum(M)/len(M)
estimador_p = media_muestral/8
print(f"Estimador de p: {estimador_p}")


N = [0 for i in range(max(M)+1)]
for i in M:
    N[i] += 1
for i in range(len(N)):
    print(f"Frecuencia de N{i} = {N[i]}")

def prob_binomial(n, p, x):
    c = math.factorial(n)/(math.factorial(x)*math.factorial(n-x))
    pp = p ** x
    np = (1-p)**(n-x)
    return (c * pp * np)
    
def T_estadistico_bin(N, n, p):
    T = 0
    for i in range(len(N)):
        den = sum(N)*prob_binomial(n, p, i)
        T += (N[i] - den)**2 / den
    return T

t0 = T_estadistico_bin(N, 8, estimador_p)
print("T estadístico ejercicio 5:", t0)
print(f"p-valor con chi^2:   {chi2.sf(t0, 7):.5f}")

def sim_bin(Nsims=1000):
    pvalor = 0
    for _ in range(Nsims):
        muestra = np.random.binomial(n=8, p=estimador_p, size=18)
        N = [0 for i in range(9)]
        m_muestral = sum(muestra)/len(muestra)
        p_estimado = m_muestral/8
        for i in muestra:
            N[i] += 1
        T_est = T_estadistico_bin(N, 8, p_estimado)
        if T_est > t0:
            pvalor += 1
    return pvalor/Nsims

print("Valor estimado del p-valor simulando frecuencias:", sim_bin())