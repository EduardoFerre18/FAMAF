from random import random
import math

def exponencial(lamda):
    U = 1-random()
    return -math.log(U)/lamda

def comp():
    y = exponencial(1)
    U = random()
    return U**(1/y)