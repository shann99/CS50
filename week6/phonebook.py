import csv
# people = {
#     "Carter": "+1-617-495-1000",
#     "David": "+1-949-468-2750"
# }

# name = input("Name: ")
# if name in people:
#     print(f"Number: {people[name]}")
name = input("Name: ")
number = input("Number: ")

with  open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, number])

