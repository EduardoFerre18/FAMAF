import random
import math

def N():
    n = 0
    sum_t = 0
    while sum_t <= 1:
        sum_t += random.random()
        n += 1
    return n


def M():
    predecesor = random.random()
    sucesor = random.random()
    n = 2
    while sucesor >= predecesor:
        predecesor = sucesor
        sucesor = random.random()
        n += 1
    return n

def estimador_e(d=0.01, nsim=10):
    media = M()
    scuad = 0
    n = 1
    while n <= nsim or scuad/n >= d:
        n += 1
        x = M()
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return n, media, scuad

result = estimador_e()

print(f"Estimación de e deteniendonos cuando la varianza del estimador es menor a 0.01: {result[1]}")
print(f"Varianza del estimador: {result[2]/result[0]}")
print(f"Iteraciones necesarias: {result[0]}")
print(f"Valor real de e: {math.exp(1)}")


def estimador_e_intervalo(l, z_alfa_2, Nsim=100):
    d = l / (2 * z_alfa_2)
    mean = N()
    scuad = 0
    n = 1
    while n <= Nsim or math.sqrt(scuad/n) > d:
        n += 1
        m = N()
        media_ant = mean
        mean = media_ant + (m - media_ant)/n
        scuad = scuad * (1 - 1/(n-1)) + n * (mean - media_ant)**2
    return n, mean, scuad, (mean-z_alfa_2*math.sqrt(scuad/n), mean+z_alfa_2*math.sqrt(scuad/n))

result = estimador_e_intervalo(0.1, 1.96)

print(f"Cantidad de simulaciones necesarias: {result[0]}")
print(f"Valor estimado de e (media): {round(result[1], 4)}")
print(f"Valor real de e ≈ {round(math.exp(1), 4)}")
print(f"Intervalo de confianza del 95%: {(round(result[3][0], 4), round(result[3][1], 4))}")