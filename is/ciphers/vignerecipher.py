def generate_key(msg, key):
    key = list(key)
    if len(msg) == len(key):
        return key
    else:
        for i in range(len(msg) - len(key)):
            key.append(key[i % len(key)])
    return "".join(key)


def encrypt(msg: str, key: str):
    msg = msg.upper()
    key = generate_key(msg, key.upper())
    ciphertext = ""

    for i in range(len(msg)):
        if msg[i].isalpha():
            p = ord(msg[i]) - ord('A')
            k = ord(key[i]) - ord('A')

            c = (p + k) % 26
            ciphertext += chr(c + ord('A'))
        else:
            ciphertext += msg[i]

    return ciphertext


def decrypt(ciphertext: str, key: str):
    key = generate_key(ciphertext, key.upper())
    msg = ""

    for i in range(len(ciphertext)):
        if ciphertext[i].isalpha():
            c = ord(ciphertext[i]) - ord('A')
            k = ord(key[i]) - ord('A')

            p = (c - k) % 26
            msg += chr(p + ord('A'))
        else:
            msg += ciphertext[i]

    return msg


msg = input("Enter the plain message: ")
key = input("Enter the key: ")

cipher = encrypt(msg, key)

print("Ciphertext:", cipher)
print("Decrypted:", decrypt(cipher, key))