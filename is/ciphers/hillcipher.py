def encrypt(msg: str):
    msg = msg.upper().replace(" ", "")
    ciphertext = ""

    key = [[3,3],
           [2,5]]

    if len(msg) % 2 != 0:
        msg += 'X'

    for i in range(0, len(msg), 2):

        p1 = ord(msg[i]) - ord('A')
        p2 = ord(msg[i+1]) - ord('A')

        c1 = (key[0][0]*p1 + key[0][1]*p2) % 26
        c2 = (key[1][0]*p1 + key[1][1]*p2) % 26

        ciphertext += chr(c1 + ord('A'))
        ciphertext += chr(c2 + ord('A'))

    return ciphertext


def mod_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x


def decrypt(cipher):
    msg = ""

    key = [[3,3],
           [2,5]]

    det = key[0][0]*key[1][1] - key[0][1]*key[1][0]
    det = det % 26

    det_inv = mod_inverse(det, 26)

    inv_key = [
        [( key[1][1] * det_inv) % 26, (-key[0][1] * det_inv) % 26],
        [(-key[1][0] * det_inv) % 26, ( key[0][0] * det_inv) % 26]
    ]

    for i in range(0, len(cipher), 2):

        c1 = ord(cipher[i]) - ord('A')
        c2 = ord(cipher[i+1]) - ord('A')

        p1 = (inv_key[0][0]*c1 + inv_key[0][1]*c2) % 26
        p2 = (inv_key[1][0]*c1 + inv_key[1][1]*c2) % 26

        msg += chr(p1 + ord('A'))
        msg += chr(p2 + ord('A'))

    return msg


msg = input("Enter the plain message: ")

cipher = encrypt(msg)

print("Ciphertext:", cipher)
print("Decrypted:", decrypt(cipher))