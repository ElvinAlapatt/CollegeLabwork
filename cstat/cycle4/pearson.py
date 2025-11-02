import numpy as np

A = [10,20,35,14,18]
B = [11,78,41,5,1]

corr_matrix = np.corrcoef(A,B)
pr = corr_matrix[0][1]
print(pr)
