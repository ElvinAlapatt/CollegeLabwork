#aim -> to find words , characters , lines
w = 0
c = 0
l = 0

f = open("cycle5/sample.txt","r")

fullstr = f.read()
c = len(fullstr)
print(c)
f.seek(0)
lines = f.readlines()
l = len(lines)
print(l)
f.seek(0)
total_words = []
for i in lines:
    words = i.split()
    for j in words:
        total_words.append(j)
print(total_words)
w = len(total_words)
print(w)
f.close()