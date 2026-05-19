from sympy import mod_inverse , gcd

def key_generation():
    p = int(input("Enter p : "))
    q = int(input("Enter q : "))
    n = p*q 
    phi = (p-1)*(q-1)

    possible_e_vals = [e for e in range(2,phi) if gcd(e,phi)==1]

    print("Possible e values : ",possible_e_vals)
    e = int(input("Enter the e value : "))

    d = mod_inverse(e,phi)

    return (d,n) , (e,n)

def encryption(M,publickey):
    e,n = publickey
    c = pow(M,e,n)
    return c

def decryption(C,privatekey):
    d,n = privatekey
    m = pow(C,d,n)
    return m

privatekey , publickey = key_generation()
message = int(input("Enter the value to encrypt : "))

encrypted_message = encryption(message,publickey)

decrypted_message = decryption(encrypted_message,privatekey)

print("Encrypted Message : ",encrypted_message,"\nDecrypted Message : ",decrypted_message)