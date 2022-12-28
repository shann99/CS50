agree = input("do you agree? ").lower()

if agree in ["y", "yes"]:
    print("agreed")
elif agree in ["n", "no"]:
    print("disagree")