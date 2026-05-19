def gen_key(plaintext:str , key : str):
    ekey = ""
    l = len(plaintext)
    lk = len(key)
    i = 0
    j = 0
    while i < l:
        if j == len(key):
            j = 0
        ekey = ekey + key[j]
        i+=1
        j+=1
    return ekey

def encrypt(plaintext: str , key : str):
    ciphertext = ""
    i = 0
    while i < len(plaintext):
        pval = ord(plaintext[i]) - ord('A')
        kval = ord(key[i]) - ord('A')
        ciphertext += chr(((pval+kval)%26)+ord('A'))
        i+=1
    return ciphertext

def decrypt(ciphertext,key):
    plaintext = ""
    i = 0
    while i < len(ciphertext):
        pval = ord(ciphertext[i]) - ord('A')
        kval = ord(key[i]) - ord('A')
        plaintext += chr(((pval-kval)%26)+ord('A'))
        i+=1
    return plaintext

p = input("Enter the plaintext : ").upper()
plain = p.replace(" ","")
ik = input("Enter the Key : ").upper()
k = ik.replace(" ","")
nk = gen_key(plain,k)
print(gen_key(plain,k))
print(encrypt(plain,nk))
print(decrypt(encrypt(plain,nk),nk))