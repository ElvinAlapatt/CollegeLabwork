def encrypt(msg: str):
    ciphertext = ""
    a = 5
    b = 8

    for i in msg:
        if i.isalpha():
            start = ord('A') if i.isupper() else ord('a')
            x = ord(i) - start
            new_char = chr(((a * x + b) % 26) + start)
            ciphertext += new_char
        else:
            ciphertext += i

    return ciphertext


def mod_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x


def decrypt(ciphertxt: str):
    msg = ""
    a = 5
    b = 8
    a_inv = mod_inverse(a, 26)

    for i in ciphertxt:
        if i.isalpha():
            start = ord('A') if i.isupper() else ord('a')
            x = ord(i) - start
            new_char = chr(((a_inv * (x - b)) % 26) + start)
            msg += new_char
        else:
            msg += i

    return msg


msg = input("Enter the plain message : ")
print(encrypt(msg))
print(decrypt(encrypt(msg)))