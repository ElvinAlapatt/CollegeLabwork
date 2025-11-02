def fib(n):
    if n <= 0:
        return 0 
    elif n == 1:
        return 1
    else:
        return (fib(n-1) + fib(n-2))
    
num = int(input("Enter the number  : "))

for i in range(0,num):
    print(fib(i))