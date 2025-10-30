rows = int(input("Enter the number of rows : "))
cols = int(input("Enter the number of cols : "))

sparse = {}
sm = []

for i in range(0,rows):
    r = []
    for j in range(0,cols):
        num = int(input("Enter the element  : "))
        r.append(num)
        if num!=0:
            sparse[(i,j)]=num
    sm.append(r)

print("The normal matrix : \n",sm)
print("\nThe sparse matrix : \n",sparse)