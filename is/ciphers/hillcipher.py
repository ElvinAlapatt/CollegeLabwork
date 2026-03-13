'''

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

'''
import numpy as np

key = np.array([[6,24,1],
                [13,16,10],
                [20,17,15]])

def encrypt(msg):
    msg = msg.upper().replace(" ","")

    while len(msg) % 3 != 0:
        msg += "X"

    cipher = ""

    for i in range(0,len(msg),3):

        block = np.array([
            ord(msg[i]) - ord('A'),
            ord(msg[i+1]) - ord('A'),
            ord(msg[i+2]) - ord('A')
        ])

        result = key.dot(block) % 26

        cipher += "".join(chr(x + ord('A')) for x in result)

    return cipher


def decrypt(cipher):

    inv_key = np.linalg.inv(key)

    # convert to modular inverse
    det = int(round(np.linalg.det(key)))
    det_inv = pow(det, -1, 26)

    adj = np.round(det * inv_key).astype(int)

    inv_key_mod = (det_inv * adj) % 26

    msg = ""

    for i in range(0,len(cipher),3):

        block = np.array([
            ord(cipher[i]) - ord('A'),
            ord(cipher[i+1]) - ord('A'),
            ord(cipher[i+2]) - ord('A')
        ])

        result = inv_key_mod.dot(block) % 26

        msg += "".join(chr(int(x) + ord('A')) for x in result)

    return msg

msg = input("Enter the message: ")
cipher = encrypt(msg)

print("Ciphertext:", cipher)
print("Decrypted:", decrypt(cipher))

'''
def encrypt(msg: str):
    msg = msg.upper().replace(" ", "")
    ciphertext = ""

    key = [[6,24,1],
           [13,16,10],
           [20,17,15]]

    # padding
    while len(msg) % 3 != 0:
        msg += 'X'

    for i in range(0, len(msg), 3):

        p1 = ord(msg[i]) - ord('A')
        p2 = ord(msg[i+1]) - ord('A')
        p3 = ord(msg[i+2]) - ord('A')

        c1 = (key[0][0]*p1 + key[0][1]*p2 + key[0][2]*p3) % 26
        c2 = (key[1][0]*p1 + key[1][1]*p2 + key[1][2]*p3) % 26
        c3 = (key[2][0]*p1 + key[2][1]*p2 + key[2][2]*p3) % 26

        ciphertext += chr(c1 + ord('A'))
        ciphertext += chr(c2 + ord('A'))
        ciphertext += chr(c3 + ord('A'))

    return ciphertext


def mod_inverse(a, m):
    for x in range(1, m):
        if (a*x) % m == 1:
            return x


def matrix_inverse(key):

    a,b,c = key[0]
    d,e,f = key[1]
    g,h,i = key[2]

    # determinant
    det = (a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g)) % 26

    det_inv = mod_inverse(det,26)

    # adjoint matrix
    adj = [
        [(e*i - f*h), -(b*i - c*h), (b*f - c*e)],
        [-(d*i - f*g), (a*i - c*g), -(a*f - c*d)],
        [(d*h - e*g), -(a*h - b*g), (a*e - b*d)]
    ]

    inv = []

    for row in adj:
        new_row=[]
        for val in row:
            new_row.append((val*det_inv)%26)
        inv.append(new_row)

    return inv


def decrypt(cipher):

    msg = ""

    key = [[6,24,1],
           [13,16,10],
           [20,17,15]]

    inv_key = matrix_inverse(key)

    for i in range(0,len(cipher),3):

        c1 = ord(cipher[i]) - ord('A')
        c2 = ord(cipher[i+1]) - ord('A')
        c3 = ord(cipher[i+2]) - ord('A')

        p1 = (inv_key[0][0]*c1 + inv_key[0][1]*c2 + inv_key[0][2]*c3) % 26
        p2 = (inv_key[1][0]*c1 + inv_key[1][1]*c2 + inv_key[1][2]*c3) % 26
        p3 = (inv_key[2][0]*c1 + inv_key[2][1]*c2 + inv_key[2][2]*c3) % 26

        msg += chr(p1 + ord('A'))
        msg += chr(p2 + ord('A'))
        msg += chr(p3 + ord('A'))

    return msg


msg = input("Enter the plain message: ")

cipher = encrypt(msg)

print("Ciphertext:", cipher)
print("Decrypted:", decrypt(cipher))
'''