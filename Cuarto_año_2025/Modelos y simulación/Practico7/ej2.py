from scipy.stats import chi2
import numpy as np

p_valor = chi2.sf(2.18, df=5)

def sim_dados(Nsim):
    pvalor = 0
    for _ in range(Nsim):
        muestra = np.random.randint(1, 7, 1000)
        N = [0 for i in range(7)]
        for i in muestra:
            N[i] += 1
        T = 0
        for i in range(1, 7):
            T += (N[i] - 1000*1/6)**2 / (1000*1/6)
        if T > 2.18:
            pvalor += 1
    return pvalor/Nsim

print(f"Valor estimado de p-valor: {sim_dados(1000)}")
print(f"Valor de p-valor con chi^2: {p_valor}")