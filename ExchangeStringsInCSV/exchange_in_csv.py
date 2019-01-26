"""
***************************************************
*  Python script for exchanging names in csv-files
***************************************************
*  Copyright (c) 2018 Felix Weichselgartner
***************************************************
"""

import fileinput, string, sys

def file_lenght(fname):
    """evaluates the amount of lines the file has
    
    Arguments:
        fname {string} -- name of the translation-list
    
    Returns:
        [int] -- number of line the file has
    """

    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1

def fill_list(Matrix, amount, filename):
    """fills the Matrix with the translation-list
        Matrix[n][0] is the old string
        Matrix[n][1] is the new string
    
    Arguments:
        Matrix {list} -- Matrix that contains the old string and the new string
        amount {integer} -- the amount of old and new string that are saved in the Matrix
        filename {string} -- name of the translation-list
    """

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
    """searches the exchange file for the old string and replaces them with new one
    
    Arguments:
        Matrix {list} -- Matrix that contains the old string and the new string
        exchange_file {string} -- name of the file where the old string are searched and replaced
        amount {integer} -- the amount of old and new string that are saved in the Matrix
    """

    for v in range(amount):
        for line in fileinput.input(exchange_file, inplace=1):
            line = line.replace(Matrix[v][0], Matrix[v][1])
            sys.stdout.write(line)

def main():
    """
    * This is a skript which requires a translation list.
    * The translation list should be a .csv-file and have each translation per line.
    * In the list there should be old string and new string divided by a ;.
    * example:
    *          old string; new string\n
    * The skript reads all the translations in a Matrix.
    * It then searches the exchange_file for the old strings and replaces them with the new ones
    """

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