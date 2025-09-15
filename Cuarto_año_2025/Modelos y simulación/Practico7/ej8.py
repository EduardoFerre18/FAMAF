import random 
import numpy as np
import math

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

def normal_acum(x):
    if x >= 0:
        Fi = math.erf(x/math.sqrt(2.))/2.+0.5
    else:
        Fi = 0.5-math.erf(-x/math.sqrt(2.))/2.
    return Fi

def rt(df): # df grados de libertad
    x = random.gauss(0.0, 1.0)
    y = 2.0*random.gammavariate(0.5*df, 2.0)
    return x / (math.sqrt(y/df))

def normal_tstudents(n):
    muestra = []
    for _ in range(n):
        muestra.append(rt(11))
    d = D(muestra, normal_acum)
    pvalor = sim_pvalor(d, n, 10000)
    return d, pvalor

print("n = 10", normal_tstudents(10))
print("n = 20", normal_tstudents(20))
print("n = 100", normal_tstudents(100))
print("n = 1000", normal_tstudents(1000))