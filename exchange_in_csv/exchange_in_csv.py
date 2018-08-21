"""
***************************************************
*  Python script for exchanging names in csv-files
***************************************************
*  Copyright (c) 2018 Felix Weichselgartner
***************************************************
"""

import fileinput, string, sys

def file_lenght(fname): #works
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1

def fill_list(Matrix, amount, filename): #works
    for x in range(amount):
        for y in range(2):
            Matrix[x][y] = ''
    flag = 0
    k = 0
    with open(filename) as f:
        while True:
            c = f.read(1)
            if not c:
                break
            if c == ';':
                flag = 1
            if c == '\n':
                flag = 0
                k = k + 1
            if not c == ';' and not c == '\n':
                Matrix[k][flag] += c

def replace(Matrix, exchange_file, amount):
    for v in range(amount):
        for line in fileinput.input(exchange_file, inplace=1):
            line = line.replace(Matrix[v][0], Matrix[v][1])
            sys.stdout.write(line)

def main():
    filename = input('Wie ist der Name der Übersetzungsliste?: ')
    read = open(filename,'r')
    amount = file_lenght(filename)
    read.close()
    Matrix = [[0 for x in range(2)] for y in range(amount)] 
    fill_list(Matrix, amount, filename)

    exchange_file = input('Wie ist der Name der Datei in der ersetzt werden soll?: ')
    replace(Matrix, exchange_file, amount)

    print('finished!')


if __name__ == "__main__": main()