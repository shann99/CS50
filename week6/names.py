import sys
names = ["Ginny", "Percy", "Bill", "Charlie", "Fred", "George", "Ron"]

if "Ron" in names:
    print("Found")
    sys.exit(0)

print("Not found")
sys.exit(1)