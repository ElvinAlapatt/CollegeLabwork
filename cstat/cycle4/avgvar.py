import numpy as np
lst = []
n = int(input("Enter the number of terms : "))
for i in range(n):
    val = int(input("Enter the element : "))
    lst.append(val)
arr = np.array(lst)

m = np.mean(arr)
v = np.var(arr)
s = np.std(arr)

print(f"m : {m} ; v : {v} ; s : {s}")