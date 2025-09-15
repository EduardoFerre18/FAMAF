import numpy as np

def D(muestra, f):
    muestra.sort()
    m = 0
    for i in range(1, len(muestra)+1):
        x = muestra[i-1]
        n = len(muestra)
        m = max(m, (i)/n - f(x), f(x) - (i-1)/n)
    return m

d = D([0.06, 0.12, 0.18, 0.27, 0.33, 0.36, 0.72, 0.74, 0.77, 0.83], (lambda x: x))
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

print("Valor estimado del p-valor:", sim_pvalor(d, 10, 10000))