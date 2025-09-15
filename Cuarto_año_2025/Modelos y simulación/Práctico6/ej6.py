import random
import math

def bernoulli_circulo(radio):
    x = random.uniform(-1, 1)
    y = random.uniform(-1, 1)
    return math.sqrt(x**2+y**2) <= radio

def estimador_proporcion(radio, d):
    p = 0
    n = 0
    while n <= 100 or math.sqrt(p * (1-p) / n) > d:
        n += 1
        x = bernoulli_circulo(radio)
        p = p + (x - p) / n
    return p

print(f"Proporción de puntos que caen dentro del círculo: {estimador_proporcion(1, 0.01)}")


def estimador_intervalo(radio, z_alfa_2, l, Nsim=100):
    d = l / (2 * z_alfa_2)
    mean = bernoulli_circulo(radio)
    scuad = 0
    n = 1
    while n <= Nsim or math.sqrt(scuad/n) > d:
        n += 1
        m = 4 * bernoulli_circulo(radio)
        media_ant = mean
        mean = media_ant + (m - media_ant)/n
        scuad = scuad * (1 - 1/(n-1)) + n * (mean - media_ant)**2
    return n, mean, scuad/n, (mean-z_alfa_2*math.sqrt(scuad/n), mean+z_alfa_2*math.sqrt(scuad/n))


result = estimador_intervalo(1, 1.96, 0.1)

print(f"Cantidad de simulaciones necesarias: {result[0]}")
print(f"Valor estimado de 𝜋 (media): {round(result[1], 4)}")
print(f"Valor real de 𝜋 ≈ {round(math.pi, 4)}")
print(f"Intervalo de confianza del 95%: {(round(result[3][0], 4), round(result[3][1], 4))}")