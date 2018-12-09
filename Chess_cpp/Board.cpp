#include "Board.hpp"
#include <windows.h>
#include <iostream>
using namespace std;

const char PAWN = 'P', ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', KING = 'K', QUEEN = 'Q', EMPTY = ' ';
const char WHITE = 'w', BLACK = 'b', NONE = 'n';

Board::Board() {
    /*
    This is how an initialised board looks like:
    ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    the top line is black
    the bottom line is white
    */
    board[0][0] = new Rook(ROOK, WHITE);
    board[0][1] = new Knight(KNIGHT, WHITE);
    board[0][2] = new Bishop(BISHOP, WHITE);
    board[0][3] = new King(KING, WHITE);
    board[0][4] = new Queen(QUEEN, WHITE);
    board[0][5] = new Bishop(BISHOP, WHITE);
    board[0][6] = new Knight(KNIGHT, WHITE);
    board[0][7] = new Rook(ROOK, WHITE);
    board[1][0] = new Pawn(PAWN, WHITE);
    board[1][1] = new Pawn(PAWN, WHITE);
    board[1][2] = new Pawn(PAWN, WHITE);
    board[1][3] = new Pawn(PAWN, WHITE);
    board[1][4] = new Pawn(PAWN, WHITE);
    board[1][5] = new Pawn(PAWN, WHITE);
    board[1][6] = new Pawn(PAWN, WHITE);
    board[1][7] = new Pawn(PAWN, WHITE);
    for(int i = 2; i < 6; i++) {
        for(int k = 0; k < fieldsize; k++) {
            board[i][k] = new Piece();
        }
    }
    board[6][0] = new Pawn(PAWN, BLACK);
    board[6][1] = new Pawn(PAWN, BLACK);
    board[6][2] = new Pawn(PAWN, BLACK);
    board[6][3] = new Pawn(PAWN, BLACK);
    board[6][4] = new Pawn(PAWN, BLACK);
    board[6][5] = new Pawn(PAWN, BLACK);
    board[6][6] = new Pawn(PAWN, BLACK);
    board[6][7] = new Pawn(PAWN, BLACK);
    board[7][0] = new Rook(ROOK, BLACK);
    board[7][1] = new Knight(KNIGHT, BLACK);
    board[7][2] = new Bishop(BISHOP, BLACK);
    board[7][3] = new King(KING, BLACK);
    board[7][4] = new Queen(QUEEN, BLACK);
    board[7][5] = new Bishop(BISHOP, BLACK);
    board[7][6] = new Knight(KNIGHT, BLACK);
    board[7][7] = new Rook(ROOK, BLACK);
}

void Board::print_board() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int k = 7, l = 8; k >= 0; k--, l--) {
        cout << l << "| ";
        for (int i = 0; i < fieldsize; i++) {
        	if (board[k][i]->getColor() == WHITE) {
                SetConsoleTextAttribute(hConsole, 111);
                cout << board[k][i]->getPiece() << ' ';
                SetConsoleTextAttribute(hConsole, 15);
            } else {
                SetConsoleTextAttribute(hConsole, 96);
        		cout << board[k][i]->getPiece() << ' ';
                SetConsoleTextAttribute(hConsole, 15);
        	}
        }
        cout << endl;
        }
    cout << "   ----------------" << endl << "   A B C D E F G H" << endl;
}
bool Board::check(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
    bool temp = board[z_from][s_from]->movement(&NewBoard, z_from, z_to, s_from, s_to);
    if (!temp)
        cout << "This move is not possible. Please enter a new move" << endl;
	return temp;
}
int Board::winner(int z_from, int z_to, int s_from, int s_to) {
	int help = 0;
	if (board[z_to][s_to]->getPiece() == KING && board[z_to][s_to]->getColor() == WHITE)
    		help = -1;
    if (board[z_to][s_to]->getPiece() == KING && board[z_to][s_to]->getColor() == BLACK)
    	help = 1;
    if (help == 1)
		return 1; //WHITE WON
    if (help == -1)
    	return -1; //BLACK WON
	return 0; //NOBDY WON YET
}
void Board::change_place(char figure, char c, int z, int s) {
	switch(figure) {
        case PAWN: {
			board[z][s] = new Pawn(PAWN, c);
            break;
        }
        case ROOK: {
			board[z][s] = new Rook(ROOK, c);
            break;
        }
        case KNIGHT: {
			board[z][s] = new Knight(KNIGHT, c);
            break;
        }
        case BISHOP: {
			board[z][s] = new Bishop(BISHOP, c);
            break;
        }
        case KING: {
			board[z][s] = new King(KING, c);
            break;
        }
        case QUEEN: {
			board[z][s] = new Queen(QUEEN, c);
            break;
        }
		case EMPTY: {
			board[z][s] = new Piece();
			break;
		}
        default: break;
    }
}
void Board::change(int z_from, int z_to, int s_from, int s_to) {
	change_place(board[z_from][s_from]->getPiece(), board[z_from][s_from]->getColor(), z_to, s_to);
	change_place(EMPTY, NONE, z_from, s_from);
}
bool Board::IsEmpty(int z, int s) {
	if (board[z][s]->getPiece() == EMPTY)
    	return true;
	else
		return false;
}