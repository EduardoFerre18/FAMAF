from random import random
import math 

def a():
    U = random()
    if U <= 1/4:
        return 2 + 2 * math.sqrt(U)
    else:
        return 6 - 6 * math.sqrt((1 - U) / 3)
    
def b():
    U = random()
    if U <= 21/35:
        return -3 + (math.sqrt(324 + 420 * U)) / 6
    else:
        return ((35 * U - 19) / 2) ** (1 / 3)
    
def c():
    U = random()
    if U <= 1/16:
        return math.log(16 * U) / 4
    else: 
        return (16 * U - 1) / 4
    

print("Ejercicio 1")
print("a) ", a())
print("b) ", b())
print("c) ", c())
    
