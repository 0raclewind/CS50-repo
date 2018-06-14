# Prints mario pyramid of selected height on screen

from cs50 import get_int

# Ask for positive integer up to 23
while True:
    height = get_int("Height: ")
    if height >= 0 and height < 24:
        break

# define steps
steps = 2

# main pyramid loop
for i in range(height):

    # calculate space count
    spaces = (height - steps) + 1

    # print spaces on screen
    for space in range(spaces):
        print(" ", end="")
    # print hashes on screen
    for step in range(steps):
        print("#", end="")

    # increment steps
    steps += 1
    print()