from cs50 import get_float
coins = 0

while True:
    change = get_float("Changed owed: ")
    if change <= 0:
        change = get_float("Changed owed: ")
    if change > 0:
        break


dollar = round(change * 100)

while dollar >= 25:
    dollar = dollar - 25
    coins += 1
while dollar >= 10 and dollar < 25:
    dollar = dollar - 10
    coins += 1
while dollar >= 5 and dollar < 10:
    dollar = dollar - 5
    coins += 1
while dollar >= 1 and dollar < 5:
    dollar = dollar - 1
    coins += 1

print(f"{coins}")