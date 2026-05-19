def encrypt(plaintext,a,b):
    ciphertext = ""
    for i in plaintext:
        if i.isalpha():
            if i.isupper():
                ciphertext += chr(((a*(ord(i)-ord('A'))+b) %26) + ord("A"))
            if i.islower():
                ciphertext += chr(((a*(ord(i)-ord('a'))+b) %26) + ord("a"))
        else:
            ciphertext += i
    return ciphertext

def mod_inv(a):
    for i in range(1,26):
        if (a*i)%26 == 1:
            return i 

def decrypt(ciphertext,a,b):
    plaintext = ""
    a_inv = pow(a,-1,26) #this is power() base,exponent,modular arithmetic
    #a_inv = mod_inv(a)
    for i in ciphertext:
        if i.isalpha():
            if i.isupper():
                plaintext += chr((a_inv * ((ord(i)-ord('A'))-b)%26)+ord('A'))
            if i.islower():
                plaintext += chr((a_inv * ((ord(i)-ord('a'))-b)%26)+ord('a'))
        else:
            plaintext += i 
    return plaintext

p = input("Enter the plain text : ")
at = int(input("Enter a (a should be coprime with 26): "))
bt = int(input("Enter b : "))
print(encrypt(p,at,bt))
print(decrypt(encrypt(p,at,bt),at,bt))