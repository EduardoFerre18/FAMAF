from scipy.stats import chi2
import numpy as np

# x = 1 - chi2.cdf(0.8617, df=2)
p_valor = chi2.sf(0.8617, df=2)

def sim_mendel(Nsim):
    pvalor= 0
    for i in range (Nsim):
        N1 = np.random.binomial(564, 1/4)
        N2 = np.random.binomial(564-N1, (1/2)/(1-1/4))
        N3 = 564 - N2 - N1
        T = (N1 - 564*1/4)**2 / (564*1/4)
        T += (N2 - 564*1/2)**2 / (564*1/2)
        T += (N3 - 564*1/4)**2 / (564*1/4)
        if T >= 0.8617:
            pvalor += 1
    return pvalor/Nsim

print(f"Valor estimado de p-valor: {sim_mendel(10000)}")
print(f"Valor de p-valor con chi^2: {p_valor}")