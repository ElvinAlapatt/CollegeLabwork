import numpy as np

A = np.array([[1,2],[3,4]])
B = np.array([[0,5],[6,7]])
k = np.kron(A,B)
print(k)