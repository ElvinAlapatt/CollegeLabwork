import hashlib
#
s1 = input("Enter string 1 : ")
s2 = input("Enter string 2 : ")

h1 = hashlib.sha256(s1.encode()).hexdigest()
h2 = hashlib.sha256(s2.encode()).hexdigest()

print(f"H1 : {h1}\nH2 : {h2}")

#

h1_bytes = bytes.fromhex(h1)
h2_bytes = bytes.fromhex(h2)

#

h1_int = int.from_bytes(h1_bytes)#,byteorder='big'
h2_int = int.from_bytes(h2_bytes)

#

xor_result = h1_int ^ h2_int
bit_difference = bin(xor_result).count('1')

print("Number of different bits = ",bit_difference)