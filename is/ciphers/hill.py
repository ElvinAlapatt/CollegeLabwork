import numpy as np


def encrypt(plaintext,key_m):
    plaintext = plaintext.upper().replace(" ","")

    while len(plaintext)%2 != 0:
        plaintext+= 'X'

    ciphertext = ""

    for i in range(0,len(plaintext),2):
        block = plaintext[i:i+2] #has i and i+1 here if the questions uses 3by3 matrix change 2 to 3

        p_block = np.array([[ord(char)-ord('A')] for char in block])  #this is making it a vector of 2*1 size

        #print("\nC_BLOCK IS -------------------------------\n",p_block)

        c_block = np.dot(key_m,p_block) % 26 #this is making it a vector of 2*1 size

        #print("\nC_BLOCK IS -------------------------------\n",c_block)

        for row in c_block:

            #print("\n----------EACH ROW IS ----------",row[0],sep="*")
            
            ciphertext += chr(int(row[0] + ord('A')))   #each row is basically having only 1 elemnt and thats why we use 0
        
    return ciphertext

key = np.array([[3,4],[5,6]])
p = input("Enter the plaintext : ")
c = encrypt(p,key)
print(c)