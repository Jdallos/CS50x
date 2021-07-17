from cs50 import get_int

# repeat until correct value recieved
while True:
    height = get_int("Height (1-8): ")
    if height >= 1 and height <= 8:
        break
    else:
        # no break so reprompt
        print("Height must be between 1- 8")

# for loop up to height, i goes 0 through height (not inclusive of height)
for i in range(0, height):
    # number of spaces is height-1 for top line, and 1 less for each new line (as i increases), within the loop decrease by 1 until height-1 reaches i.
    for j in range(height-1, i, -1):
        print(" ", end="")
    # print i + 1 blocks, so i=0 loop prints 1, while max i=7 prints 8. 8 Num is not inclusive in range(8) but 0-7 gives 8 iterations.
    for j in range(0, i + 1):
        print("#", end="")
    print()
