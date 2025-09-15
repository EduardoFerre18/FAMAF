import numpy as np
import math
import random
from scipy.stats import chi2

# Ejercicio 2

print(" ---- Ejercicio 2 ---- \n")

data = [15.22860536, 40.60145536, 33.67482894, 44.03841737, 15.69560109, 16.2321714, 25.02174735, 30.34655637, 3.3181228, 5.69447539, 10.1119561, 49.10266584, 3.6536329, 35.82047148, 3.37816632, 36.72299321, 50.67085322, 3.25476304, 20.12426236, 20.2668814, 17.49593589, 2.70768636, 14.77332745, 1.72267967, 23.34685662, 8.46376635, 9.18330789, 9.97428217, 2.33951729, 137.51657441, 9.79485269, 10.40308179, 1.57849658, 6.26959703, 4.74251574, 1.53479053, 34.74136011, 27.47600572, 9.1075566, 1.88056595, 27.59551348, 6.82283137, 12.45162807, 28.01983651, 0.36890593, 7.82520791, 3.17626161, 46.91791271, 38.08371186, 41.10961135]

#b)
def D(muestra, f):
    muestra.sort()
    m = 0
    for i in range(1, len(muestra)+1):
        x = muestra[i-1]
        n = len(muestra)
        m = max(m, (i)/n - f(x), f(x) - (i-1)/n)
    return m

d = D(data, (lambda x: 1 - math.exp(-x * 0.05)))
print(f"El valor del estadistico es: {d}")

#c)
def sim_pvalor(d_KS, n, Nsim):
    pvalor = 0
    for _ in range(Nsim):
        uniformes = np.random.uniform(0,1,n)
        uniformes.sort()
        d_sim = D(uniformes, (lambda x: x))
        if d_sim > d_KS:
            pvalor += 1
    return pvalor/Nsim

p_valor_ej2 = sim_pvalor(d, len(data), 10000)
print(f"p-valor usando uniformes: {p_valor_ej2:.5f}")
if p_valor_ej2 < 0.04:
    print("Se rechaza la hipotesis nula con un nivel de rechazo del 4%.")
else:
    print("No se rechaza la hipotesis nula con un nivel de rechazo del 4%.")


#d)
def pvalor_exp(lamda, d0, size, Nsims=10000):
    pvalor = 0
    for i in range(Nsims):
        muestra = np.random.exponential(1/lamda, size)
        d_j = D(muestra, (lambda x: 1 - math.exp(-x*lamda)))
        if d_j > d0:
            pvalor += 1
    return pvalor/Nsims

p_valor_exp = pvalor_exp(0.05, d, len(data), 10000)
print(f"p-valor usando exponencial: {p_valor_exp:.5f}")
if p_valor_exp < 0.04:
    print("Se rechaza la hipotesis nula con un nivel de rechazo del 4% (simulando variables que verifican la hipotesis nula).")
else:
    print("No se rechaza la hipotesis nula con un nivel de rechazo del 4% (simulando variables que verifican la hipotesis nula).")
print("\n")

# Ejercicio 3

print(" ---- Ejercicio 3 ---- \n")

estimador_p = 0.494

#b) 
def prob_binomial(n, p, x):
    c = math.factorial(n)/(math.factorial(x)*math.factorial(n-x))
    pp = p ** x
    np = (1-p)**(n-x)
    return (c * pp * np)

M = [0, 1, 2, 3, 4, 5]
N = [38, 144, 342, 287, 164, 25]

def T_estadistico_bin(N, n, p):
    T = 0
    for i in range(len(N)):
        den = sum(N)*prob_binomial(n, p, i)
        T += (N[i] - den)**2 / den
    return T

t = T_estadistico_bin(N, 5, estimador_p)
print("estadístico t :", t)
p_valor_chi2 = chi2.sf(t, 4)
print(f"p-valor con chi^2: {p_valor_chi2:.5f}")

#c)

def sim_pvalor_binomial(t, n, p, Nsim):
    pvalor = 0
    for _ in range(Nsim):
        muestra = np.random.binomial(n, p, 1000)
        N = [0 for _ in range(n + 1)]
        for x in muestra:
            N[x] += 1
        p_actualizado = np.sum(muestra) / (len(muestra) * n)
        T = 0
        for i in range(len(N)):
            den = 1000 * prob_binomial(n, p_actualizado, i)
            T += (N[i] - den) ** 2 / den
        if T >= t:
            pvalor += 1        
    return pvalor / Nsim

p_valor_bin = sim_pvalor_binomial(t, 5, estimador_p, 1000)
print(f"p-valor usando 1000 simulaciones: {p_valor_bin:.5f}")

#d)

if p_valor_chi2 < 0.05:
    print("Se rechaza la hipotesis nula con un nivel de rechazo del 5%.")
else:
    print("No se rechaza la hipotesis nula con un nivel de rechazo del 5%.")

print("\n")

# Ejercicio 4
print(" ---- Ejercicio 4 ---- \n")

def ejercicio4(funciong, a, b, z_alfa_2, l, Nsim): #z_alfa_2 = z_(alfa/2)
    'Confianza = (1 - alfa)%, amplitud del intervalo: L'
    d = l / (2 * z_alfa_2)
    media = funciong(a + (b-a) * random.random()) * (b-a)
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        x = funciong(a + (b-a) * random.random()) * (b-a)
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return (n, media, math.sqrt(scuad), (media - z_alfa_2 * math.sqrt(scuad/n), media + z_alfa_2 * math.sqrt(scuad/n)))

resultado = ejercicio4((lambda x: math.exp(-x) * (1 - x**4)), 2, 3, 1.96, 0.002, 100)
n = resultado[0]
media = resultado[1]
desvio = resultado[2]
intervalo = tuple(round(value, 4) for value in resultado[3])

print(f"Cantidad de simulaciones necesarias: {n}")
print(f"Valor estimado de la integral(media): {'%.4f'%media}")
print(f"Desvío estándar muestral: {round(desvio, 4)}")
print(f"Intervalo de confianza del 95%: {intervalo} \n")


print("Tabla de resultados:")
print(f"{'N° de sim.':<12} {'I':<15} {'S':<25} {'IC(95%)':<35}")
print(ejercicio4((lambda x: math.exp(-x) * (1 - x**4)), 2, 3, 1.96, 2*1.96, 1000))
print(ejercicio4((lambda x: math.exp(-x) * (1 - x**4)), 2, 3, 1.96, 2*1.96, 5000))
print(ejercicio4((lambda x: math.exp(-x) * (1 - x**4)), 2, 3, 1.96, 2*1.96, 7000))

