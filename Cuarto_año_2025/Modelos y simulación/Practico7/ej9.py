import math
import numpy as np

def D(muestra, f):
    muestra.sort()
    m = 0
    for i in range(1, len(muestra)+1):
        x = muestra[i-1]
        n = len(muestra)
        m = max(m, (i)/n - f(x), f(x) - (i-1)/n)
    return m

def sim_pvalor(d_KS, n, Nsim):
    pvalor = 0
    for _ in range(Nsim):
        uniformes = np.random.uniform(0,1,n)
        uniformes.sort()
        d_sim = D(uniformes, (lambda x: x))
        if d_sim > d_KS:
            pvalor += 1
    return pvalor/Nsim


M = [1.6, 10.3, 3.5, 13.5, 18.4, 7.7, 24.3, 10.7, 8.4, 4.9, 7.9, 12, 16.2, 6.8, 14.7]
media_muestral = sum(M)/len(M)
estimador_lambda = 1/media_muestral
d0 = D(M, (lambda x: 1 - math.exp(-x*estimador_lambda)))

print("Valor estadístico d:", d0)
print("Valor estimado de p-valor con uniformes:", sim_pvalor(d0, len(M), 10000))

def pvalor_exp(lamda, d0, size, Nsims=10000):
    pvalor = 0
    for i in range(Nsims):
        muestra = np.random.exponential(1/lamda, size)
        media_muestral = sum(muestra)/len(muestra)
        lambda_estimado = 1/media_muestral
        d_j = D(muestra, (lambda x: 1 - math.exp(-x*lambda_estimado)))
        if d_j > d0:
            pvalor += 1
    return pvalor/Nsims
        
print("Valor estimado de p-valor con exponenciales", pvalor_exp(estimador_lambda, d0, len(M)))
print("En ambos casos p-valor > 0.01, con un nivel de rechazo del 1% no se rechaza H0")