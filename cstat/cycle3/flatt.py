import numpy as np

arr = np.arange(6).reshape(2,3)
print("Original Array  : \n",arr)

f = arr.flatten()
print("Flattened array is : \n",f)