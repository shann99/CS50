while True:
    try:
        height = int(input("height: "))
        if (height >= 1) and (height <= 8):
            break
    except:
        print("please type in a number between 1 and 8")
i = 0
for i in range(height):
    for j in range(height-1, i, -1):
        print(" ", end="")
    for z in range(-1, i):
        print("#", end="")
    print("  ", end="")
    for a in range(-1, i):
        print("#", end="")
    print("")