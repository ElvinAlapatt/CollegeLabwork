import numpy as np
import matplotlib.pyplot as plt
lst = [10,25,35,30,50]
arr = np.array(lst)

plt.plot(arr)
plt.title("Array to Line")
plt.ylabel("elements")
plt.xlabel("index")
plt.grid(True)
plt.tight_layout()
plt.show()