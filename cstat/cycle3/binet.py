import numpy as np
#phi = (1 + root5)/2
#psi = (1 - root5)/2
# f = (phi - psi)/root5
def fibonacci(n):
    sqrt5 = np.sqrt(5)
    phi = (1 + sqrt5)/2
    psi = (1 - sqrt5)/2
    indices = np.arange(n)
    fib = ((phi**indices) - (psi**indices))/sqrt5
    return np.rint(fib).astype('int')

num = int(input("Enter the number of terms : "))
fib = fibonacci(num)
print(fib)   