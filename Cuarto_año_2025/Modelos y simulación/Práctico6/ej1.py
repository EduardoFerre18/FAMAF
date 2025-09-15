import numpy as np
import math 
def ej1():
    media = np.random.normal()
    muestra = [media]
    n = 1
    scuad = 0
    while n <= 100 or math.sqrt(scuad / n) >  0.1:
        n += 1
        x = np.random.normal()
        muestra.append(x)
        media_ant = media 
        media =  media_ant + (x - media_ant) / n
        scuad = scuad * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    return muestra, media, scuad

resultado = ej1()
muestra = resultado[0]
media = resultado[1]
varianza = resultado[2]
print("El número de datos generados efectivamente es: ", len(muestra) )
print("La media muestral es: ", media )
print("La varianza muestral es: ", varianza )