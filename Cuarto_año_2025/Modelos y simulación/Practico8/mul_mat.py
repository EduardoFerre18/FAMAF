import numpy as np

# Ejercicio 1
Q = np.array([[0.25, 0.5, 0.25], [0.5, 0, 0.5], [0.5, 0, 0.5]])

C = np.dot(Q, Q)
Q2 = np.linalg.matrix_power(Q, 2)
Q3 = np.linalg.matrix_power(Q, 3)
Q4 = np.linalg.matrix_power(Q, 4)

'''
print(f"Q^2:\n{Q2}\n")
print(f"Q^3:\n{Q3}\n")
print(f"Q^4:\n{Q4}\n")
'''


# Ejercicio 2
A = np.array([[1/2, 1/4, 1/4], [1/3, 0, 2/3], [1/2, 1/2, 0]])
A2 = np.linalg.matrix_power(A, 2)
# print(f"A^2:\n{A2}\n")

# Ejercicio 3
B = np.array([[1/2, 1/2], [2/3, 1/3]])
B2 = np.linalg.matrix_power(B, 3)
print(f"B^3:\n{B2}\n")