#
#   Encrypts text using vigenere cipher by key specified
#

import sys

# alphabet variables
lower = 'abcdefghijklmnopqrstuvwxyz'
upper = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def main():
    # check for correct argument input
    if len(sys.argv) != 2 or not str.isalpha(sys.argv[1]) or len(sys.argv[1]) < 1:
        print("Usage: python caesar.py k")
        exit(1)
    else:
        key = str.lower(sys.argv[1])
        plain = input("plaintext: ")
        cipher = ""
        index_array = []
        array_index = 0
        key_index = 0

        # loop for making cipher text
        for letter in plain:
            index_array.append(lower.find(str.lower(key[key_index])))
            if key_index == len(key) - 1:
                key_index = 0
            else:
                key_index += 1
            if letter.islower():
                char_index = lower.find(letter)
                cipher += lower[(char_index + index_array[array_index]) % 26]
                array_index += 1
            elif letter.isupper():
                char_index = upper.find(letter)
                cipher += upper[(char_index + index_array[array_index]) % 26]
                array_index += 1
            else:
                cipher += letter

        print(f"ciphertext: {cipher}")


if __name__ == "__main__":
    main()