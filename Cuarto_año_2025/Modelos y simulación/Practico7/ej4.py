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

d = D([86.0, 133.0, 75.0, 22.0, 11.0, 144.0, 78.0, 122.0, 8.0, 146.0, 33.0, 41.0, 99.0], (lambda x: 1 - math.exp(-x/50)))
print(f"El valor del estadistico es: {d}")

def sim_pvalor(d_KS, n, Nsim):
    pvalor = 0
    for _ in range(Nsim):
        uniformes = np.random.uniform(0,1,n)
        uniformes.sort()
        d_sim = D(uniformes, (lambda x: x))
        if d_sim > d_KS:
            pvalor += 1
    return pvalor/Nsim

print("Valor estimado del p-valor:", sim_pvalor(d, 13, 10000))