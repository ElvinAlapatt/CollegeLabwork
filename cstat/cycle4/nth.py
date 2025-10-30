import numpy as np

lst = []
n = int(input("Enter the number of elts : "))
for i in range(0,n):
    val = int(input("Enter the elements : "))
    lst.append(val)

nth = int(input("Enter the order of difference : "))
data = np.array(lst)
difference = np.diff(data , n=nth)
print(difference)