import numpy as np
rows = int(input("Enter the number of rows : "))

sparse = {}
sm = []

for i in range(0,rows):
    r = []
    for j in range(0,rows):
        num = int(input("Enter the element  : "))
        r.append(num)
        if num!=0:
            sparse[(i,j)]=num
    sm.append(r)
A = np.array(sm)

eigen_values , eigen_vectors = np.linalg.eig(A)
print(f"Eigen Values : \n{eigen_values}\nEigen Vectors : \n{eigen_vectors}")