from random import random
import math

# a) Desarrolle métodos para generar las siguientes variables aleatorias

# i) Distribución Pareto: f(x) = ax^{-(a+1)} 1≤x<∞, a>0
def pareto(a):
    U = random()
    return (1 / (1 - U) ** (1 / a))


# ii) Distribución Erlang: f(x) = (x^(k-1) * e^(-x/μ)) / μ^k (k-1)! 0≤x<∞, μ>0, k entero

def erlang(k, mu):
    prod = 1
    for _ in range(k):
        prod *= (1 - random())
    gamma = -(math.log(prod)/mu)
    return gamma 

# iii) Distribución de Weibull: f(x) = β/λ * (x/λ)^(β-1) * e^-(x/λ)^β 0≤x<∞, λ>0, β>0

def weibull(lamda, beta):
    U = random()
    return lamda * (-math.log(1- U)) ** (1 / beta)


#b) 
'''
Estime la media de cada variable con 10.000 repeticiones, usando los parámetros a = 2, µ =
2, k = 2, λ = 1, β = 2. Busque en la web los valores de las esperanzas para cada variable
con estos parámetros (cuidado con las parametrizaciones) y compare los valores obtenidos.
'''
def estimate_mean(distribution, *params):
    n = 10000
    total = 0
    for _ in range(n):
        total += distribution(*params)
    return total / n
# Estimaciones
pareto_mean = estimate_mean(pareto, 2)
erlang_mean = estimate_mean(erlang, 2, 1/2)
weibull_mean = estimate_mean(weibull, 1, 2)
# Valores teóricos
pareto_theoretical = 2 / (2 - 1)
erlang_theoretical = 2 * 2
weibull_theoretical = 1 * math.gamma(1+1/2)
# Comparación
print(f"Media estimada de Pareto: {pareto_mean}, Media teórica: {pareto_theoretical}")
print(f"Media estimada de Erlang: {erlang_mean}, Media teórica: {erlang_theoretical}")
print(f"Media estimada de Weibull: {weibull_mean}, Media teórica: {weibull_theoretical}")
