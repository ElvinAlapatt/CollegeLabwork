import numpy as np
A = np.arange(27).reshape(3,3,3)
print("Original Array : \n",A)
diagonals = []
# d = A.diagonal(axis1=-2,axis2=-1)
# print("Diagonals are : \n",d)
for i in range(A.shape[0]):
    d = np.diagonal(A[i])
    arr = np.array(d)
    diagonals.append(arr)
print("2D slice are : \n",diagonals)