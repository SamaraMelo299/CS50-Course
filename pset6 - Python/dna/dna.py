import csv
import sys

def longest_match(dna_sequence, subsequence):
    max_length = 0
    sub_length = len(subsequence)

    for i in range(len(dna_sequence)):
        length = 0
        while dna_sequence[i:i+sub_length] == subsequence:
            length += 1
            i += sub_length
        max_length = max(max_length, length)

    return max_length

def main():

    # Verifica o uso da linha de comando
    if len(sys.argv) != 3:
        sys.exit("python dna.py data.csv sequence.txt")

    # Lê arquivo de banco de dados em uma variável
    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Lê o arquivo de sequência de DNA em uma variável
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()

    # Encontra a correspondência mais longa de cada STR na sequência de DNA
    subsequences = list(database[0].keys())[1:]

    result = {}
    for subsequence in subsequences:
        result[subsequence] = longest_match(dna_sequence, subsequence)

    # Verifica o banco de dados para perfis correspondentes
    for person in database:
        match = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == result[subsequence]:
                match += 1

        # Se todas as subsequências corresponderem
        if match == len(subsequences):
            print(person["name"])
            return

    print("No match")

if __name__ == "__main__":
    main()
