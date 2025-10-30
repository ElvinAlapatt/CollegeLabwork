import numpy as np

arr = np.array([[2,4,5],[5,6,7],[12,34,65]])

np.savetxt("output.csv",arr,fmt="%d",delimiter=',')