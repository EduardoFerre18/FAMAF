import random
import math


def N():
    n = 0
    sum_t = 0
    while sum_t <= 1:
        sum_t += random.random()
        n += 1
    return n

def muestra_n(Nsim=1000):
    media = N()
    scuad = 0
    for n in range(2, Nsim):
        m = N()
        media_ant = media
        media = media_ant + (m - media_ant)/n
        scuad = scuad * (1 - 1/(n-1)) + n * (media - media_ant)**2
    return media, scuad

def muestra_n_intervalo(l, z_alfa_2, Nsim=1000):
    d = l / (2 * z_alfa_2)
    media = N()
    scuad = 0
    n = 1
    while n <= Nsim or math.sqrt(scuad/n) > d:
        n += 1
        m = N()
        media_ant = media
        media = media_ant + (m - media_ant)/n
        scuad = scuad * (1 - 1/(n-1)) + n * (media - media_ant)**2
    return n, media, scuad, (media-z_alfa_2*math.sqrt(scuad/n), media+z_alfa_2*math.sqrt(scuad/n))

def simulacion_varianza(Nsim=1000):
    suma = 0
    for n in range(1, Nsim+1):
        e_aprox = muestra_n()[0]
        suma += (3 * e_aprox - e_aprox**2)/Nsim
    return suma/Nsim


intervalo = muestra_n_intervalo(0.025, 1.96, Nsim=1000)
varianza = round((3*math.exp(1) - math.exp(1)**2)/1000, 6)
mean = muestra_n()[0]
var = muestra_n()[1] 

print(f"Estimacion de e: {mean}")
print(f"Valor estimado de Var(N_barra) con 1000 simulaciones: {round(simulacion_varianza(), 6)}")
print(f"Valor real de Var(N_barra) con n=1000:   {varianza}")
print(f"Varianza muestral con 1000 simulaciones:   {round(var, 6)}")
print(f"Intervalo de confianza del 95%: {tuple(round(value, 4) for value in intervalo[3])}")
print(f"Cantidad de simulaciones necesarias para que el IC tenga longitud de a lo sumo 0.025: {intervalo[0]}")