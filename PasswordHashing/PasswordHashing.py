import hashlib

def hashing(password):
    _hash_ = hashlib.md5(str(password).encode('utf-8')).hexdigest()
    return _hash_

def main():
    password = input('enter password to be hashed by md5: ')
    password_hashed = hashing(password)
    print('your hashed password is: ' + str(password_hashed))

if __name__ == "__main__":
    main()