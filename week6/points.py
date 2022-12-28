points = int(input("how many points did you lose? "))

if points < 2: 
    print("you lost less points than me")
elif points > 2:
    print("you lost more points than me")
else:
    print("we lost the same amount of points")