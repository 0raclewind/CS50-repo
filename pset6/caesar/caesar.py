#
#   Encrypts text using caesar cipher by key specified
#

import sys

# alphabet variables
lower = 'abcdefghijklmnopqrstuvwxyz'
upper = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def main():
    # check for correct argument input
    if len(sys.argv) != 2 or isinstance(sys.argv[1], int):
        print("Usage: python caesar.py k")
        exit(1)
    else:
        key = int(sys.argv[1])
        plain = input("plaintext: ")
        cipher = ""

        # loop for making cipher text
        for letter in plain:
            if letter.islower():
                char_index = lower.find(letter)
                cipher += lower[(char_index + key) % 26]
            elif letter.isupper():
                char_index = upper.find(letter)
                cipher += upper[(char_index + key) % 26]
            else:
                cipher += letter

        print(f"ciphertext: {cipher}")


if __name__ == "__main__":
    main()