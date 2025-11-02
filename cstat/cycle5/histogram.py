import matplotlib.pyplot as plt

lst = [160,155,170,168,162,140,144,158,153,156]

plt.hist(lst,bins=4,edgecolor = 'black')
plt.title("Histogram of heights Distribution")
plt.xlabel('Height in cm')
plt.ylabel('Number of students')
plt.grid(axis='y')
plt.show()