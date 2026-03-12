def encrypt(msg : str):
    ciphertext = ""
    shift = 3

    for i in msg:
        if i.isalpha():
            start = ord('A') if i.isupper() else ord('a')
            new_char = chr((ord(i)-start + shift) % 26 + start)
            ciphertext += new_char
        else:
            ciphertext += i
    return ciphertext

def decrypt(ciphertxt : str):
    msg = ""
    shift = 3

    for i in ciphertxt:
        if i.isalpha():
            start = ord('A') if i.isupper() else ord('a')
            new_char = chr((ord(i)-start - shift) % 26 + start)
            msg += new_char
        else:
            msg += i
    return msg

msg = input("Enter the plain message : ")
print(encrypt(msg))
print(decrypt(encrypt(msg)))