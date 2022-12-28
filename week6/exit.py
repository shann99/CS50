from sys
if len(argv) != 2: 
    print("missing command-line argument")
   sys.exit(1)

print(f"hello, {argv[1]}")
sys.exit(0)