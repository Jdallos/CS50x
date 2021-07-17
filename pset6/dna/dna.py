import csv
import sys


def main():
    # check for correct num of cmd args
    if not len(sys.argv) == 3:
        print("Error, require 2 command line arguments")
        sys.exit(1)

    # open and read to dict, then dict to list, csv with people dna
    with open(sys.argv[1]) as dbase:
        # this gives access to fieldnames method/the str's. Also can iterate over each row
        reader = csv.DictReader(dbase)
        # reader into list gives access to the whole dictionary file as a list
        people = list(reader)

    # open and read the dna to be matched into a variable
    with open(sys.argv[2]) as sequ:
        sequence = sequ.read()

# count max repeats of STR's in sequence,
    maxStrCounts = []
# get the str's from reader.fieldnames and iterate over each one
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        # set maxStrCounts[i] to 0 to allow comparison
        maxStrCounts.append(0)
        # Iterate through sequence, if matching str[i] add to count
        for j in range(len(sequence)):
            count = 0
            # syntax compares from j through sequence length of j +STR
            if sequence[j:(j + len(STR))] == STR:
                # Adding the previous matched STR length and continuing to check if the next substring is a match
                k = 0
                while sequence[j + k: (j + k + len(STR))] == STR:
                    # k accumulates the length of a match STR
                    k += len(STR)
                    count += 1
                # remember we are starting i at 1 but indexing into MaxStrCounts from 0
                if count > maxStrCounts[i - 1]:
                    maxStrCounts[i - 1] = count

# if counts all match  with person in csv, print out matching name, else no match
# iterate through the list of people
    for i in range(len(people)):
        match = 0
        # loop through str names from fieldnames (skip 0=name)
        for j in range(1, len(reader.fieldnames)):
            # count sample sequence max counts (adjusted for indexing from 0) matches against the counts on database, indexing people by str label
            # converting the counts from strings to ints
            if int(maxStrCounts[j - 1]) == int(people[i][reader.fieldnames[j]]):
                match += 1
            # if match count is same as database person, we have a match
            if match == (len(reader.fieldnames) - 1):
                print(people[i]["name"])
                exit(0)

    print("No match")


main()