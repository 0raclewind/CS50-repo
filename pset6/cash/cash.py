from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

# coin count variable
coinCount = 0

# Conversion to cents
cents = change * 100

while cents > 0:
    # check for quaters
    if cents >= 25:
        cents -= 25

    # check for dimes
    elif cents >= 10:
        cents -= 10

    # check for nickels
    elif cents >= 5:
        cents -= 5

    # check for pennies
    else:
        cents -= 1

    coinCount += 1

print(coinCount)