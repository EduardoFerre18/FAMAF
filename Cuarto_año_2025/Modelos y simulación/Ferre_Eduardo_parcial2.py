from random import random

# Ejercicio 1

def f(x):
    return 30 * (x**2 - 2*x**3 + x**4)

def ejercicio1():
    c = 1.875
    while True:
        Y = random()
        U = random()
        if U < f(Y) / c:
            return Y
        
def estimar_esp(Nsims):
    suma = 0
    for _ in range(Nsims):
        suma += ejercicio1()
    return suma / Nsims

print("El valor esperado de X es: ", estimar_esp(10000))

# Ejercicio 2

def codigoX(p):
    U = random()
    i = 10
    P = p
    F = P
    while U > F:
        P *= (1 -p)
        F += P
        i += 1
    return i

def estimar_esp_p(Nsims):
    suma = 0
    for _ in range(Nsims):
        suma += codigoX(0.5)
    return suma / Nsims

print("El valor esperado de X para p = 0.5 es: ", estimar_esp_p(10000))
