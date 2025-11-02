import numpy as np
def read_matrix():
    rows = int(input("Enter the number of rows : "))
    cols = int(input("Enter the number of cols : "))

    sm = []

    for i in range(0,rows):
        r = []
        for j in range(0,cols):
            num = int(input("Enter the element  : "))
            r.append(num)
        sm.append(r)
    return sm 

A = read_matrix()
B = read_matrix()
expression = input("Enter the einstein expression : ")
result = np.einsum(expression,A,B)
print(result)