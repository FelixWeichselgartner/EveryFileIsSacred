#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Pieces.hpp"
#define fieldsize 8

/*
* class Board contains:
* attributes:
* + the board on which will be played
* methods:
* + constructor to initilise the board
* + print_board to output the board to commandline
* + check 
* + winner
* + change_place
* + change
* + IsEmpty
*/

class Board {
    public:
		class Piece *board[fieldsize][fieldsize];
        Board();
        void print_board();
		bool check(Board, int, int, int, int);
		int winner(int, int, int, int);
		void change_place(char, char, int, int);
		void change(int, int, int, int);
		bool IsEmpty(int, int);   
};

#endif