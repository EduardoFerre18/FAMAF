from random import random, uniform
import math
from timeit import timeit

'''
Escriba tres programas para generar un variable aleatoria normal patrón, usando

a) generación de variables exponenciales según el ejemplo 5 f del libro Simulacion de S. M. Ross,
b) el método polar,
c) el método de razón entre uniformes

Pruebe los códigos calculando la media muestral y varianza muestral de 10.000 valores generados con los
tres métodos.

'''

# a)

def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

def Normal_rechazo(mu, sigma):
    while True:
        Y1 = exponencial(1)
        Y2 = exponencial(1)
        if Y2 >=(Y1-1) ** 2 / 2:
            if random() < 0.5:
                return Y1 * sigma + mu
            else:
                return -Y1 * sigma + mu

# b)

def Normal_polar(mu, sigma):
    Rcuadrado = exponencial(1/2)
    Theta = uniform(0, 2 * math.pi)
    X = math.sqrt(Rcuadrado) * math.cos(Theta)
    Y = math.sqrt(Rcuadrado) * math.sin(Theta)
    return X * sigma + mu, Y * sigma + mu


def Polar_Box_Muller(mu,sigma):
    #Generar un punto aleatorio en el cırculo unitario. ´
    while True:
        V1, V2 = uniform(-1, 1), uniform(-1, 1)
        if V1 ** 2 + V2 ** 2 <= 1:
            S = V1 ** 2 + V2 ** 2
            X = V1 * math.sqrt(-2 * math.log(S) / S)
            Y = V2 * math.sqrt(-2 * math.log(S) / S)
            return ( X * sigma + mu, Y * sigma + mu)

# c)
    
def razon_uniforme(mu, sigma):
    NV_MAGICCONST = 4 * math.exp(-0.5) / math.sqrt(2.0)
    while 1:
        u1 = random()
        u2 = 1.0 - random()
        z = NV_MAGICCONST * (u1 - 0.5) / u2
        zz = z * z / 4.0
        if zz <= -math.log(u2):
            break
    return mu + z * sigma

def esp_var_normal(fun, mu, sigma, Nsims=10000):
    esp = 0
    for _ in range(Nsims):
        result = fun(mu, sigma)
        if type(result) == tuple:
            esp += result[0]
        else:
            esp += result
    esp = esp/Nsims
    var = 0
    for _ in range(Nsims):
        result = fun(mu, sigma)
        if type(result) == tuple:
            var += (result[0] - esp)**2
        else:
            var += (result - esp)**2
    return (esp, var/Nsims)

print(f"Esperanza y varianza usando el método de rechazo: {esp_var_normal(Normal_rechazo, 1.2, 3)}")
print(f"Esperanza y varianza usando el método polar: {esp_var_normal(Normal_polar, 1.2, 3)}")
print(f"Esperanza y varianza usando el método de razón entre uniformes: {esp_var_normal(razon_uniforme, 1.2, 3)}")
print("Valores reales: E[X] = 1.2, Var[X] = 9")
print("\n")