/*
**************************************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
**************************************************************
*  Date of creating this file: 02.12.2018
*  Last changes: 03.12.2018
*  creator: Felix Weichselgartner
*  purpose: learning OOP
**************************************************************
*  original upload to:
*  https://github.com/FelixWeichselgartner/EveryFileIsSacred
**************************************************************
*  This is a Chess game in C++
*  based on a previous Chess game in C
*  also to find in the repository mentioned above
**************************************************************
*/

#include <iostream>
#include <windows.h>
#include "Pieces.hpp"
#include "Board.hpp"
using namespace std;

const char PAWN = 'P', ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', KING = 'K', QUEEN = 'Q', EMPTY = ' ';
const char WHITE = 'w', BLACK = 'b', NONE = 'n';

/*
* class Chess contains:
* attributes:
* - the current turn
* methods:
* + gameloop
* + input function
*/

class Chess {
    private:
        int turn; //0 is white, 1 is black

    public:
		Chess();
        int input(Board, int *, int *, int *, int *, int);
        int gameloop();
};

Chess::Chess() {
	turn = 1;
}

int Chess::input(Board NewBoard, int *z_from, int *z_to, int *s_from, int *s_to, int turn) {
	char S_from, S_to;

	//this is for checking the color
	Board * newBoard = &NewBoard;

	do {
		
    	cout << "which figure do you want to move?: ";
    	cin >> S_from >> *z_from;
    	if (S_from == '+' && *z_from == 1)
    		return 11;
    	if (*z_from < 0 || *z_from > 8 || S_from > 'H' || S_from < 'A')
    		return 44;
    	*s_from = S_from - 65; *z_from -= 1;
		if(((turn % 2 == 1) && newBoard->board[*z_from][*s_from]->getColor() == BLACK) || ((turn % 2 == 0) && newBoard->board[*z_from][*s_from]->getColor() == WHITE))
			return false; //return color false
		if(NewBoard.IsEmpty(*z_from, *s_from))
			return false;

    	cout << "where do you want to move it to?: ";
    	cin >> S_to >> *z_to;
    	*s_to = S_to - 65; *z_to -= 1; //convert input in the fitting array-format
	} while(*z_to < 0 || *z_to > 8 || S_to > 'H' || S_to < 'A');
    return true;
}

int Chess::gameloop() {
	int win = 0, z_from, z_to, s_from, s_to;
	bool check, binput;
    Board NewBoard;
	do {
		system("cls");
		NewBoard.print_board();
		do {
			do {
				binput = input(NewBoard, &z_from, &z_to, &s_from, &s_to, turn);
				if (!binput)
					cout << "wrong input!" << endl;
			} while(!binput);
			check = NewBoard.check(NewBoard, z_from, z_to, s_from, s_to);
		} while (!check);
		NewBoard.change(z_from, z_to, s_from, s_to);
		turn++;
		win = NewBoard.winner(z_from, z_to, s_from, s_to);
	} while (win == 0);
	return win;
}

int main() {
    class Chess NewGame;
    int endofgame;
    endofgame = NewGame.gameloop();
	switch(endofgame) {
		case 1: cout << "white won" << endl;
		case -1: cout << "black won" << endl;
		default: cout << "error accured" << endl;
	}
	cout << "press any button to close the game!" << endl;
    int wait;
    cin >> wait;
    return 0;
}