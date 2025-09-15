import numpy as np
import math 
import random

def integral_ninf0(funciong, d, Nsim):
    y = random.random()
    media = (1/pow(y, 2))*funciong(-(1/(y)) + 1)
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        y = random.random()
        x = (1/pow(y, 2))*funciong(-(1/(y)) + 1)
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return media


def integral_ab_intervalo(funciong, a, b, z_alfa_2, l, Nsim): #z_alfa_2 = z_(alfa/2)
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

def integral_0inf_intervalo(funciong, z_alfa_2, l, Nsim): #z_alfa_2 = z_(alfa/2)
    'Confianza = (1 - alfa)%, amplitud del intervalo: L'
    d = l / (2 * z_alfa_2)
    y = random.random()
    media = (1 / y ** 2) * funciong(((1/y) - 1))
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        y = random.random()
        x = (1 / y ** 2) * funciong(((1/y) - 1))
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return (n, media, math.sqrt(scuad), (media - z_alfa_2 * math.sqrt(scuad/n), media + z_alfa_2 * math.sqrt(scuad/n)))

def integral_ninf0_intervalo(funciong, z_alfa_2, l, Nsim): #z_alfa_2 = z_(alfa/2)
    'Confianza = (1 - alfa)%, amplitud del intervalo: L'
    d = l / (2 * z_alfa_2)
    y = random.random()
    media = (1 / y ** 2) * funciong(-(1/(y)) + 1)
    n = 1
    scuad = 0
    while n < Nsim or math.sqrt(scuad/n) >= d:
        n += 1
        y = random.random()
        x = (1 / y ** 2) * funciong(-(1/(y)) + 1)
        media_ant = media
        media = media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return (n, media, math.sqrt(scuad), (media - z_alfa_2 * math.sqrt(scuad/n), media + z_alfa_2 * math.sqrt(scuad/n)))

def IntegralMonteCarlo_intervalo(funciong, a, b, z_alfa_2, l, Nsim): #z_alfa_2 = z_(alfa/2)
    'Confianza = (1 - alfa)%, amplitud del intervalo: L'
    if a != -np.inf and b != np.inf:
        result = integral_ab_intervalo(funciong, a, b, z_alfa_2, l, Nsim)
    elif b == np.inf and a != -np.inf:
        if a == 0:
            result = integral_0inf_intervalo(funciong, z_alfa_2, l, Nsim)
        else:
            result1 = IntegralMonteCarlo_intervalo(funciong, 0, b, z_alfa_2, l, Nsim)
            result2 = IntegralMonteCarlo_intervalo(funciong, a, 0, z_alfa_2, l, Nsim)
            result = (result1, result2)
    elif b != np.inf and a == -np.inf:
        if b == 0:
            result = integral_ninf0(z_alfa_2, l, Nsim)
        else:
            result1 = IntegralMonteCarlo_intervalo(funciong, 0, b, z_alfa_2, l, Nsim)
            result2 = IntegralMonteCarlo_intervalo(funciong, a, 0, z_alfa_2, l, Nsim)
            result = (result1, result2)
    elif a == -np.inf and b == np.inf:
        result1 = IntegralMonteCarlo_intervalo(funciong, 0, b, z_alfa_2, l, Nsim)
        result2 = IntegralMonteCarlo_intervalo(funciong, a, 0, z_alfa_2, l, Nsim)
        result = (result1, result2)
    return result


# i)

result_i = IntegralMonteCarlo_intervalo((lambda x: (math.sin(x)/x)), math.pi, 2*math.pi, 1.96, 0.002, 1000)
n = result_i[0]
media = result_i[1]
desvio = result_i[2]
intervalo = tuple(round(value, 4) for value in result_i[3])

print(f"Cantidad de simulaciones necesarias: {n}")
print(f"Valor estimado de la integral en el item i (media): {'%.4f'%media}")
print(f"Valor real de la integral en el ítem i ≈ {-0.4337}")
print(f"Desvío estándar muestral: {round(desvio, 4)}")
print(f"Intervalo de confianza del 95%: {intervalo}")


print(IntegralMonteCarlo_intervalo((lambda x: (math.sin(x)/x)), math.pi, 2*math.pi, 1.96, 2*1.96, 1000)) # 2 * 1.96, pues es el intervalo completo ahora
print(IntegralMonteCarlo_intervalo((lambda x: (math.sin(x)/x)), math.pi, 2*math.pi, 1.96, 2*1.96, 5000))
print(IntegralMonteCarlo_intervalo((lambda x: (math.sin(x)/x)), math.pi, 2*math.pi, 1.96, 2*1.96, 7000))

# ii)

result_ii = IntegralMonteCarlo_intervalo((lambda x: 3/(3+x**4)), 0, np.inf, 1.96, 0.002, 1000)
n = result_ii[0]
media = result_ii[1]
desvio = result_ii[2]
intervalo = tuple(round(value, 4) for value in result_ii[3])

print(f"Cantidad de simulaciones necesarias: {n}")
print(f"Valor estimado de la integral en el item i (media): {'%.4f'%media}")
print(f"Valor real de la integral en el ítem i ≈ {1.4618}")
print(f"Desvío estándar muestral: {round(desvio, 4)}")
print(f"Intervalo de confianza del 95%: {intervalo}")


print(IntegralMonteCarlo_intervalo((lambda x: 3/(3+x**4)), 0, np.inf, 1.96, 2*1.96, 1000))
print(IntegralMonteCarlo_intervalo((lambda x: 3/(3+x**4)), 0, np.inf, 1.96, 2*1.96, 5000))
print(IntegralMonteCarlo_intervalo((lambda x: 3/(3+x**4)), 0, np.inf, 1.96, 2*1.96, 7000))