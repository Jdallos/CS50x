from cs50 import get_float

# break only when positive value inputted
while True:
    due = get_float("Change due: ")
    if due > 0:
        break
    else:
        print("Please provide a non-negative value.")

# create a count for coins
coins = 0

# This avoids a rounding error
due = due * 100

# from largest coin, knock off coin value from due and add to coin count
while due >= 25:
    due -= 25
    coins += 1
while due >= 10:
    due -= 10
    coins += 1
while due >= 5:
    due -= 5
    coins += 1
while due >= 1:
    due -= 1
    coins += 1

print(coins)