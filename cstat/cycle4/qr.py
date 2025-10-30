import numpy as np
A = np.array([[10,20,30],[40,50,60],[70,80,90]])
q,r = np.linalg.qr(A)
print("Matrix Orthognal : \n",q)
print("Upper Triangular region : \n",r)
print("\nCheck if q@r equals A: ",np.allclose(A,q@r))