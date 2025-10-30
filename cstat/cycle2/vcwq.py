v = 0
c = 0
w = 0
q = 0

s = input("Enter the  string : ")
for i in s:
    if i == '?':
        q = q + 1
    elif i in 'aeiouAEIOU':
        v = v + 1
    elif i.isalpha():
        c = c + 1
    
words = s.split()
print(words,"\n")
w = len(words)
print(f"words : {w}\nvowels : {v}\nconsonents : {c}\nQuestion marks : {q}")