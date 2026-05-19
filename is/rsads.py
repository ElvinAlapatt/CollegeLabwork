from sympy import mod_inverse , gcd 

def simple_hash(message):
    hash_value = 0
    for ch in message:
        hash_value = hash_value*31 + ord(ch)
        print(hash_value,sep=" | ")
    return hash_value

p = int(input("Enter p : "))
q = int(input("Enter q : "))
n = p*q
phi = (p-1)*(q-1)
e_possible = [e for e in range(2,phi) if gcd(e,phi)==1]
print(e_possible)
e = int(input("Enter e value : "))
d = mod_inverse(e,phi)

m = input("Enter the message : ")
hash_val = simple_hash(m)

signature = pow(hash_val,d,n)
print("Signature : ",signature)

verified_signature = pow(signature,e,n)
new_hash = simple_hash(m)

if verified_signature == new_hash % n:
    print("Valid")
else:
    print("Invalid")