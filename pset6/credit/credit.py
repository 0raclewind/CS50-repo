from cs50 import get_int

cc = get_int("Number: ")
sum = 0

# specify first number index
digit_index = len(str(cc)) - 2

# First numbers loop
while digit_index >= 0:
    digit = int(str(cc)[digit_index]) * 2

    if digit > 9:
        sum += int(str(digit)[0]) + int(str(digit)[1])
    else:
        sum += digit

    digit_index -= 2

# redefine digit index for second numbers iteration
digit_index = len(str(cc)) - 1

# Second numbers loop
while digit_index >= 0:
    sum += int(str(cc)[digit_index])
    digit_index -= 2

# variables for vendor check
visa = int(str(cc)[0]) == 4
amex = int(str(cc)[:2]) == 34 or int(str(cc)[:2]) == 37
mc = int(str(cc)[:2]) in range(51, 56)

# Check if card is valid
if sum % 10 != 0:
    print("INVALID")
else:
    # vendor check
    if amex:
        print("AMEX")
    elif visa:
        print("VISA")
    elif mc:
        print("MASTERCARD")