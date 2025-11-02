stk_open = []
stk_close = []

ipstr = input("Enter the string : ")

for i in ipstr:
    if i in '{[(':
        stk_open.append(i)
    elif i in '}])':
        stk_close.append(i)
    
for i in stk_open:
    if i == '{' and stk_close[-1] == '}':
        stk_close.pop()
    elif i == '[' and stk_close[-1] == ']':
        stk_close.pop()
    elif i == '(' and stk_close[-1] == ')':
        stk_close.pop()

if not stk_close:
    print("The string is valid")
else:
    print("The string is invalid")