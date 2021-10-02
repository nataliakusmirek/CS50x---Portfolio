import csv
from sys import argv, exit


def main():
    # Ensure correct usage
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    start = argv[1]
    with open(argv[1]) as file:
        files = csv.DictReader(file)
        dic_list = list(files)
    # open csv file and open sequence file, then read contents into memory
    with open(argv[2]) as sequences:
        dna = sequences.read()

    # reads the labels of row one, names, and each type of DNA
    count = []
    for i in range(1, len(files.fieldnames)):
        STR = files.fieldnames[i]
        count.append(0)
    # Loop through sequence to find STR
        for j in range(len(dna)):
            STR_count = 0

            # j:j concept from cs50 notes
            if dna[j:(j + len(STR))] == STR:
                k = 0
                while dna[(j + k):(j + k + len(STR))] == STR:
                    STR_count += 1
                    k += len(STR)

                if STR_count > count[i - 1]:
                    count[i - 1] = STR_count

   # check if values match to a given name
   # comparison of values on line 43 from medium
    for i in range(len(dic_list)):
        match = 0
        for j in range(1, len(files.fieldnames)):
            if int(count[j - 1]) == int(dic_list[i]
                                        [files.fieldnames[j]]):
                match += 1
            if match == (len(files.fieldnames) - 1):
                print(dic_list[i]['name'])
                exit(0)


main()