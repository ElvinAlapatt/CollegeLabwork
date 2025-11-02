import numpy as np
rows = int(input("Enter the number of rows : "))
cols = int(input("Enter the number of cols : "))
m = []
for i in range(0,rows):
    r = []
    for j in range(0,cols):
        num = int(input("Enter the element  : "))
        r.append(num)
    m.append(r)
print("Original Matrix : \n",m)
numpy_array = np.array(m)
print("NumPy  array : \n",numpy_array)
lst = numpy_array.tolist()
print("Back to lst : \n",lst)