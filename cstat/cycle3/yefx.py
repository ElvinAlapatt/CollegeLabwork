import matplotlib.pyplot as plt
import numpy as np
def f(x):
    return np.sin(x)
x = np.linspace(-np.pi,np.pi,400)
y = f(x) 
plt.plot(x,y)
plt.title("Graph of y=sin(x)")
plt.tight_layout()
plt.show()