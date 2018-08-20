"""
***********************************************
*  Python - Chess program
***********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
***********************************************
"""

from math import fabs
import os
clear = lambda: os.system("cls")
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
    print('--------------------\n    A B C D E F G H')

def bishop_movement():


def rook_movement():


def check():


def put_in():
    point_place = list(map(int, input().split(' ')))


def save_game():


def catch_old():


def main():
    amount = 1
    win = 0
    game_mode = input("""type in 'n' if you want to start a new game\nyou can save by entering '+' and 1 as the position of your figure\ntype in 'o' if you want to load an old game: """)
    if game_mode == 'o':
        temp = catch_old(board, amount)
        if temp == False:
            return
        print('your old board has been loaded')
        input('press any button to begin: ')
        clear()
    else if game_mode == 'n':
        setup(board)
        input('press any button to begin: ')
        clear()
    else:
        input('please restart the game')
        return
    #background_color
    show_board(board)
    while win != -1 and win != 1:
        if amount == 1:
            print('white begins')
        win = put_in(board, amount)
        if win == 11:
            save_game(board, amount)
            print('your game has been saved')
            input('press any button to close the game')
            return
        if win == 45:
            print('there is no figure to move')
            continue
        if win == 44:
            print('out of board')
            continue
        if _TURN_ == True:
            if win == 42:
                print('its not your turn')
                continue
        clear()
        show_board(board)
        print(f'this is turn number {turn}')
        if win == 1:
            print('white wins!')
            input('press any button to close the game')
        if win == -1:
            print('black wins!')
            print('press any button to close the game')
        amount += 1

if __name__ == "__main__": main()
        