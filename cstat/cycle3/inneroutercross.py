import numpy as np
M = np.array([[1,2,3],[4,5,6]])
V = np.array([7,8,9])
inner_result = np.inner(M,V)
outer_result = np.outer(M.flatten(),V)
cross_result = np.array([np.cross(row,V) for row in M])
print(f"inner :\n{inner_result}\nOuter : \n{outer_result}\nCross : \n{cross_result}")