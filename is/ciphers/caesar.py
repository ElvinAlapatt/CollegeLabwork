def encrypt(plaintext):
    ciphertext = ""
    for i in plaintext:
        if i.isalpha():
            if i.isupper():
                ciphertext += chr( ((ord(i) - ord('A')+3)%26) + ord('A'))
            elif i.islower():
                ciphertext += chr(((ord(i) - ord('a')+3)%26) + ord('a'))
        else:
            ciphertext +=i
    return ciphertext

def decrypt(ciphertext):
    plaintext = ""
    for i in ciphertext:
        if i.isalpha():
            if i.isupper():
                plaintext += chr(((ord(i) - ord('A')-3)%26) + ord('A'))
            elif i.islower():
                plaintext += chr(((ord(i) - ord('a')-3)%26) + ord('a'))
        else:
            plaintext += i 
    return plaintext


pt = input("Enter the plain Text: ")
print(encrypt(pt))
print(decrypt(encrypt(pt)))