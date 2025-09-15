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

def sim_ej7():
    print("H0: La muestra tiene distribución esponencial con media 1")
    muestra = np.random.exponential(scale=1, size=30)
    d = D(muestra, (lambda x: 1 - math.exp(-x)))
    print(d)
    pvalor = sim_pvalor(d, 30, 10000)
    if pvalor > 0.05:
        print(f"No rechazamos H0 ya que: {pvalor} > 0.05")
    else:
        print(f"Rechazamos H0 ya que: {pvalor} < 0.05")
        
sim_ej7()