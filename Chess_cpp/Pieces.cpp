#include "Pieces.hpp"
#include "Board.hpp"
#include <iostream>

const char PAWN = 'P', ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', KING = 'K', QUEEN = 'Q', EMPTY = ' ';
const char WHITE = 'w', BLACK = 'b', NONE = 'n';

/*
* methods of class Piece
*/

Piece::Piece() {
	piece = ' ';
	color = NONE;
}

Piece::Piece(char p, char c) {
    piece = p; color = c;
}

bool Piece::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to){
	;
}

char Piece::getPiece() {
    return piece;
}

void Piece::setPiece(char set) {
    piece = set;
}

char Piece::getColor() {
    return color;
}

void Piece::setColor(char set) {
    color = set;
}


/*
* methods of class Rook
*/

Rook::Rook() {
    piece = ' ';
    color = NONE;
}

Rook::Rook(char p, char c) {
    piece = p; color = c;
}

bool Rook::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    if (NewBoard->board[z_to][s_to]->getColor() == NewBoard->board[z_from][s_from]->getColor()) {
    	return false;
    }
    if (!(z_from == z_to) && !(s_from == s_to)) {
    	return false;
    }
    if ((NewBoard->board[z_to][s_to]->getPiece() != EMPTY && (NewBoard->board[z_to][s_to]->getColor() == NewBoard->board[z_from][s_from]->getColor()))) {
    	return false;
    }
    if (z_from == z_to) {
    	for (int i = s_from; i < s_to - 1; i++) {
    		if (NewBoard->board[z_from][i + 1]->getPiece() != EMPTY) {
    			return false;
    		}
    	}
    }
    if (s_from == s_to) {
    	for (int i = z_from; i < z_to - 1; i++) {
    		if (NewBoard->board[i + 1][s_from]->getPiece() != EMPTY) {
    			return false;
    		}
    	}
    }
    return true;
}


/*
* methods of class Knight
*/

Knight::Knight(char p, char c) {
    piece = p; color = c;
}

bool Knight::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    if (NewBoard->board[z_to][z_from]->getColor() == NewBoard->board[z_from][s_from]->getColor()) {
    	return false;
    }
    /*
    * combinations: 
    *		z_to == z_from + 1 && s_to == s_from + 2 up right right
    *		z_to == z_from + 2 && s_to == s_from + 1 up up right
    *		z_to == z_from + 2 && s_to == s_from - 1 up up left
    *		z_to == z_from + 1 && s_to == s_from - 2 up left left
    *		z_to == z_from - 1 && s_to == s_from - 2 down left left
    *		z_to == z_from - 2 && s_to == s_from - 1 down down left
    *		z_to == z_from - 2 && s_to == s_from + 1 down down right
    *		z_to == z_from - 1 && s_to == s_from + 2 down right right
    *
    *		!(z_to == z_from + 1 && s_to == s_from + 2) && !(z_to == z_from + 2 && s_to == s_from + 1) && !(z_to == z_from + 2 && s_to == s_from - 1) && !(z_to == z_from + 1 && s_to == s_from - 2) && !(z_to == z_from - 1 && s_to == s_from - 2) && !(z_to == z_from - 2 && s_to == s_from - 1) && !(z_to == z_from - 2 && s_to == s_from + 1) && !(z_to == z_from - 1 && s_to == s_from + 2)
    */
    if (!(z_to == z_from + 1 && s_to == s_from + 2) && !(z_to == z_from + 2 && s_to == s_from + 1) && !(z_to == z_from + 2 && s_to == s_from - 1) && !(z_to == z_from + 1 && s_to == s_from - 2) && !(z_to == z_from - 1 && s_to == s_from - 2) && !(z_to == z_from - 2 && s_to == s_from - 1) && !(z_to == z_from - 2 && s_to == s_from + 1) && !(z_to == z_from - 1 && s_to == s_from + 2)) {
    	return false;
    }
    return true;
}


/*
* methods of class Bishop
*/

int absolute(int x) {
	if (x >= 0)
		return x;
	else return -x;
}

Bishop::Bishop() {
    piece = ' ';
    color = NONE;
}

Bishop::Bishop(char p, char c) {
    piece = p; color = c;
}

bool Bishop::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    if (NewBoard->board[z_to][s_to]->getColor() == NewBoard->board[z_from][s_from]->getColor()) {
    	return false;
    }
    int deltaLs = absolute(s_from - s_to), deltaLz = absolute(z_from - z_to), flag = 0; //the difference of old/new position
    if (z_from == z_to) {
    	return false;
    }
    else if (s_from == s_to) {
    	return false;
    }
    else if (!(deltaLs == deltaLz)) {
    	return false;
    }
    else {
    	if (z_from < z_to) {
    		for (int i = 0; i < deltaLz; i++) {
    			if (s_to > s_from) { //case 1: up and right
    				if (NewBoard->board[z_from + 1 + i][s_from + 1 + i]->getPiece() != EMPTY) {
    					if (z_from + 1 + i == z_to) {
    						if (s_from + 1 + i == s_to) {
    							flag = 1;
    						}
    					}
    					if (flag != 1)
    						return false;
    				}
    			}
    			if (s_to < s_from) { //case 2: up and left
    				if (NewBoard->board[z_from + 1 + i][s_from - 1 - i]->getPiece() != EMPTY) {
    					if (z_from + 1 + i == z_to) {
    						if (s_from - 1 - i == s_to) {
    							flag = 1;
    						}
    					}
    					if (flag != 1)
    						return false;
    				}
    			}
    		}
    	}
    	if (z_from > z_to) {
    		for (int i = 0; i > (-deltaLz); i--) {
    			if (s_to > s_from) { //case 3: down and right
    				if (NewBoard->board[z_from - 1 + i][s_from + 1 - i]->getPiece() != EMPTY) {
    					if (z_from - 1 + i == z_to) {
    						if (s_from + 1 + i == s_to) {
    							flag = 1;
    						}
    					}
    					if (flag != 1)
    						return false;
    				}
    			}
    			if (s_to < s_from) { //case 4: down and left
    				if (NewBoard->board[z_from - 1 + i][s_from - 1 + i]->getPiece() != EMPTY) {
    					if (z_from - 1 + i == z_to) {
    						if (s_from - 1 + i == s_to) {
    							flag = 1;
    						}
    					}
    					if (flag != 1)
    						return false;
    				}
    			}
    		}
    	}
    }
    return true;
}


/*
* methods of class King
*/

King::King(char p, char c) {
    piece = p; color = c;
}

bool King::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    if (z_to != z_from + 1 && z_to != z_from - 1 && s_to != s_from + 1 && s_to != s_from - 1) {
    	return false;
    }
    if ((NewBoard->board[z_to][s_to]->getPiece() != EMPTY && (NewBoard->board[z_to][s_to]->getColor() == NewBoard->board[z_from][s_from]->getColor()))) {
    	return false;
    }
    return true;
}


/*
* methods of class Queen
*/

Queen::Queen() {
    piece = ' ';
    color = NONE;
}

Queen::Queen(char p, char c) {
    piece = p; color = c;
}

bool Queen::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    if (z_from != z_to && s_from != s_to) { //bishop movement in here
	    if (Bishop::movement(NewBoard, z_from, z_to, s_from, s_to) == true) {
		    return true;
	    } else {
		    return false;
	    }
    }
    if (z_from == z_to || s_from == s_to) { //tower movement in here
	    if (Rook::movement(NewBoard, z_from, z_to, s_from, s_to) == true) {
		    return true;
	    } else {
		    return false;
	    }
    }
    return false;
}


/*
* methods of class Pawn
*/

char Pawn::read_char() {
	char c;
	do {
		std::cin >> c;
	} while (c != 'T' && c != 'S' && c != 'L' && c != 'D');
	return c;
}

Pawn::Pawn() {
    piece = ' ';
    color = NONE;
}

Pawn::Pawn(char p, char c) {
    piece = p; color = c;
}

void Pawn::pawn_transformation(Board *NewBoard, char newFigure, char c, int z, int s) {
	switch(newFigure) {
        case PAWN: {
			NewBoard->board[z][s] = new Pawn(PAWN, c);
	        break;
    	}
        case ROOK: {
			NewBoard->board[z][s] = new Rook(ROOK, c);
            break;
        }
        case KNIGHT: {
			NewBoard->board[z][s] = new Knight(KNIGHT, c);
    	    break;
        }
        case BISHOP: {
			NewBoard->board[z][s] = new Bishop(BISHOP, c);
            break;
	    }
        case KING: {
			NewBoard->board[z][s] = new King(KING, c);
            break;
        }
        case QUEEN: {
			NewBoard->board[z][s] = new Queen(QUEEN, c);
            break;
        }
		case EMPTY: {
			NewBoard->board[z][s] = new Piece();
			break;
		}
	    default: break;
	}
}

bool Pawn::movement(Board *NewBoard, int z_from, int z_to, int s_from, int s_to) {
    int beat = false, flag = 0, z, s;
	char newFigure, c;
    if (s_from != s_to) {
		if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from + 1) && !(NewBoard->board[z_to][s_to]->getPiece() == EMPTY) && NewBoard->board[z_from][s_from]->getColor() == WHITE) { //columns can be different if your figure is going to beat another
			beat = true;
			flag = 1; //white player
		}
		if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from - 1) && !(NewBoard->board[z_to][s_to]->getPiece() == EMPTY) && NewBoard->board[z_from][s_from]->getColor() == BLACK) { //black player
			beat = true;
			flag = 1;
		}
		if (flag == 0) {
			return false;
		}
	}
	if (color == WHITE) {
		if (z_from == 1) { //first time you can move 2 steps
			if (!(z_to == z_from + 1 || z_to == z_from + 2)) { //you can move 1 or 2 fields
				return false;
			}
		}
		else {
			if (!(z_to == z_from + 1)) //you can only move 1 step later
				return false;
		}
	}
	if (color == BLACK) {
		if (z_from == 6) {
			if (!(z_to == z_from - 1 || z_to == z_from - 2)) {
				return false;
			}
		}
		else {
			if (!(z_to == z_from - 1))
				return false;
		}
	}
	if (beat == false) { //pawn can only move forward if the field is empty and they are not beating another figure
		if (!(NewBoard->board[z_to][s_to]->getPiece() == EMPTY) && beat == false) {
			return false;
		}
	}
	if (z_to == 7 && NewBoard->board[z_from][s_from]->getColor() == WHITE) {
		std::cout << "which figure do you want for you pawn?: ";
		newFigure = read_char();
		z = z_to; s = s_to;
		pawn_transformation(NewBoard, newFigure, WHITE, z, s);
		
	}
	if (z_to == 0 && NewBoard->board[z_from][s_from]->getColor() == BLACK) {
		std::cout << "which figure do you want for you pawn?: ";
		newFigure = read_char();
		z = z_to; s = s_to;
		pawn_transformation(NewBoard, newFigure, BLACK, z, s);
	}
	return true;
}
