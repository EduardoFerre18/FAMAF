import math
import numpy as np
from scipy.stats import chi2,  norm

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


M = [91.9, 97.8, 111.4, 122.3, 105.4, 95.0, 103.8, 99.6, 96.6, 119.3, 104.8, 101.7]
media_muestral = sum(M)/len(M)
var_m = 0
for i in M:
    var_m += (i - media_muestral)**2
desvio_m = math.sqrt(var_m/(len(M)-1))

mu_estimado = media_muestral
sigma_estimado = desvio_m
d0 = D(M, (lambda x: norm.cdf(x, mu_estimado, sigma_estimado)))
print("Estadístico d:", d0)
print("Valor estimado de p-valor con uniformes:", sim_pvalor(d0, len(M), 10000))

def pvalor_normal(mu, sigma, d0, size, Nsims=1000):
    pvalor = 0
    for i in range(Nsims):
        muestra = norm.rvs(loc=mu, scale=sigma, size=size)
        mu_estimado = sum(muestra)/size
        sigma_estimado = 0
        for i in muestra:
            sigma_estimado += (i - mu_estimado)**2
        sigma_estimado = math.sqrt(sigma_estimado/(size-1))
        d_j = D(muestra, (lambda x: norm.cdf(x, mu_estimado, sigma_estimado)))
        if d_j > d0:
            pvalor += 1
    return pvalor/Nsims

print("Valor estimado de p-valor con normales:", pvalor_normal(mu_estimado, sigma_estimado, d0, len(M)))
print("En ambos casos p-valor > 0.05, con un nivel de rechazo del 5% no se rechaza H0")