import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as database_file:
        reader = csv.DictReader(database_file)
        #getting only the columns names from database file
        fieldnames = reader.fieldnames
  
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_file:
        text = dna_file.readline()
        
    # TODO: Find longest match of each STR in DNA sequence
    #initalizing empty array
    dna = []
    #fieldname (aka column names) that don't equal "names", call longest_match on the DNA
    for fieldname in fieldnames:
            if fieldname != "name":
                #sequence and match it against text (aka the DNA sequence file)
                count = longest_match(text, fieldname)
                #append the counts to a list + convert counts to string for easy comparison
                dna.append(str(count))

    person = []
    # TODO: Check database for matching profiles
    #opening file again but with csv.reader not csv.DictReader
    with open(sys.argv[1], "r") as database_file:
        reader = csv.reader(database_file)
        #skipping header line
        next(reader)
        #appending each row to person list
        for row in reader:
           person.append(row)

    #initializing an empty string
    match = ""
    #looping through each row in person and slicing off the first column(names)
    for item in person:
        #checking if there is a match b/w every column after name and with dna (the array that counts up the STR)
        if item[1:] == dna:
            #if there is a match, set match to equal first column (the name of the matched person) of that row
            match = item[0]
    #if there is no match (aka match stays as an empty string), return no match, else return the name
    if match == "":
        print("No match")
    else:
        print(match)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
