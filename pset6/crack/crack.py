#
#   Cracks passwords hashed with DES algorithm
#   works with up to five character password length
#

import sys
import crypt


def main():
    # check for correct argument input
    if len(sys.argv) != 2 or len(sys.argv[1]) < 1:
        print("Usage: python crack.py hash")
        exit(1)
    else:
        alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        given_hash = sys.argv[1]
        salt = given_hash[:2]
        guess = [0]

        for fifth_letter in range(len(alphabet)):
            for fourth_letter in range(len(alphabet)):
                for third_letter in range(len(alphabet)):
                    for second_letter in range(len(alphabet)):
                        for first_letter in range(len(alphabet)):
                            guess[0] = alphabet[first_letter]
                            crypted = crypt.crypt(''.join(guess), salt)
                            if crypted == given_hash:
                                print(''.join(guess))
                                exit(0)
                        if len(guess) == 1:
                            guess.append(alphabet[second_letter])
                        else:
                            guess[1] = alphabet[second_letter]
                    if len(guess) == 2:
                        guess.append(alphabet[third_letter])
                    else:
                        guess[2] = alphabet[third_letter]
                if len(guess) == 3:
                    guess.append(alphabet[fourth_letter])
                else:
                    guess[3] = alphabet[fourth_letter]
            if len(guess) == 4:
                guess.append(alphabet[fifth_letter])
            else:
                guess[4] = alphabet[fifth_letter]


if __name__ == "__main__":
    main()