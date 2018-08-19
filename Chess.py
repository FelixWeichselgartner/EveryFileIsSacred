"""
***********************************************
*  Python - Chess program
***********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
***********************************************
"""

from math import fabs
fieldsize = 8
_TURN_ = True
_ENCODE_ = False
_CHECK_ = True

def read_char():
    c = input('which figure do you want for your pawn?: ')
    while (c != 'T' and c != 'S' and c != 'L' and c != 'D'):
        c = input('which figure do you want for your pawn?: ')
    return c

def setup(board):
    for k in range(fieldsize):
        for i in range(fieldsize):
            board[k][i] = ' '
    board[0][0][0] = board[0][7][0] = 't'
    board[7][0][0] = board[7][7][0] = 'T'
	board[0][1][0] = board[0][6][0] = 's'
    board[7][1][0] = board[7][6][0] = 'S'
	board[0][2][0] = board[0][5][0] = 'l'
    board[7][2][0] = board[7][5][0] = 'L'
	board[0][3][0] = 'd'
    board[7][3][0] = 'D'
	board[0][4][0] = 'k'
    board[7][4][0] = 'K'
    for l in range(fieldsize):
        board[1][i] = 'b'
        board[6][i] = 'B'

def show_board(board):
    l = 8
    for m in range(7, 0, -1):
        print(f'{l}| ')
        for t in range(fieldsize):
            if (board[k][i] == #kleinbuchstabe):
                print(f'{board[k][i] }')
            else:
                print(f'{board[k][i] }')
        print('\n')
    print('--------------------\n    A B C D E F G H\n')
        