def generate_matrix(key):
    key = key.upper().replace("J", "I")
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"

    matrix = []
    used = ""

    for char in key + alphabet:
        if char not in used:
            used += char

    for i in range(0, 25, 5):
        matrix.append(list(used[i:i+5]))

    return matrix


def find_position(matrix, char):
    for i in range(5):
        for j in range(5):
            if matrix[i][j] == char:
                return i, j


def prepare_text(text):
    text = text.upper().replace("J", "I").replace(" ", "")
    prepared = ""

    i = 0
    while i < len(text):
        a = text[i]
        b = ""

        if i + 1 < len(text):
            b = text[i+1]

        if a == b:
            prepared += a + "X"
            i += 1
        else:
            if b:
                prepared += a + b
                i += 2
            else:
                prepared += a + "X"
                i += 1

    return prepared


def encrypt(text, matrix):
    text = prepare_text(text)
    ciphertext = ""

    for i in range(0, len(text), 2):
        a, b = text[i], text[i+1]

        r1, c1 = find_position(matrix, a)
        r2, c2 = find_position(matrix, b)

        if r1 == r2:
            ciphertext += matrix[r1][(c1+1) % 5]
            ciphertext += matrix[r2][(c2+1) % 5]

        elif c1 == c2:
            ciphertext += matrix[(r1+1) % 5][c1]
            ciphertext += matrix[(r2+1) % 5][c2]

        else:
            ciphertext += matrix[r1][c2]
            ciphertext += matrix[r2][c1]

    return ciphertext


def decrypt(ciphertext, matrix):
    plaintext = ""

    for i in range(0, len(ciphertext), 2):
        a, b = ciphertext[i], ciphertext[i+1]

        r1, c1 = find_position(matrix, a)
        r2, c2 = find_position(matrix, b)

        if r1 == r2:
            plaintext += matrix[r1][(c1-1) % 5]
            plaintext += matrix[r2][(c2-1) % 5]

        elif c1 == c2:
            plaintext += matrix[(r1-1) % 5][c1]
            plaintext += matrix[(r2-1) % 5][c2]

        else:
            plaintext += matrix[r1][c2]
            plaintext += matrix[r2][c1]

    return plaintext


key = input("Enter key: ")
matrix = generate_matrix(key)

print("Playfair Matrix:")
for row in matrix:
    print(row)

msg = input("Enter the plain message: ")

cipher = encrypt(msg, matrix)
print("Ciphertext:", cipher)

print("Decrypted:", decrypt(cipher, matrix))