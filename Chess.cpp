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
using namespace std;
#define fieldsize 8

/*
* P = Pawn      R = Rook
* N = Knight    B = Bishop
* K = King      Q = Queen
*/
const char PAWN = 'P', ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', KING = 'K', QUEEN = 'Q', EMPTY = ' ';
const char WHITE = 'w', BLACK = 'b', NONE = 'n';

int absolute(int x) {
	if (x >= 0)
		return x;
	else return -x;
}

class Board;

/*
* class Piece
* all other pieces are derived on this class
*/
class Piece {
    protected:
        char piece;
        char color;
    
    public:
        Piece() {
            piece = ' ';
            color = NONE;
        }
        Piece(char p, char c) {
            piece = p; color = c;
        }
		virtual bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to){
			;
		}
        char getPiece() {
            return piece;
        }
        void setPiece(char set) {
            piece = set;
        }
        char getColor() {
            return color;
        }
        void setColor(char set) {
            color = set;
        }
};

/*
* class Pawn
* derived from Pieces
* added methods:
*   +movement
*/
class Pawn: public Piece {
    public:
        Pawn() {
            piece = ' ';
            color = NONE;
        }
        Pawn(char p, char c) {
            piece = p; color = c;
        }


        /*
        doesnt fit on cpp version yet
        */
        char read_char() {
        	char c;
        	do {
        		cin >> c;
        	} while (c != 'T' && c != 'S' && c != 'L' && c != 'D');
        	return c;
        }

		void pawn_transformation(Board NewBoard, char newFigure, char c, int z, int s) {
			switch(newFigure) {
	            case PAWN: {
					NewBoard.board[z][s] = new Pawn(PAWN, c);
        	        break;
            	}
                case ROOK: {
					NewBoard.board[z][s] = new Rook(ROOK, c);
	                break;
    	        }
                case KNIGHT: {
					NewBoard.board[z][s] = new Knight(KNIGHT, c);
            	    break;
                }
	            case BISHOP: {
					NewBoard.board[z][s] = new Bishop(BISHOP, c);
    	            break;
        	    }
                case KING: {
					NewBoard.board[z][s] = new King(KING, c);
	                break;
                }
    	        case QUEEN: {
					NewBoard.board[z][s] = new Queen(QUEEN, c);
                    break;
	            }
				case EMPTY: {
					NewBoard.board[z][s] = new Piece();
					break;
				}
        	    default: break;
        	}
		}

        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
            int beat = false, flag = 0, z, s;
			char newFigure, c;
            if (s_from != s_to) {
	    		if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from + 1) && !(NewBoard.board[z_to][s_to]->getPiece() == EMPTY) && NewBoard.board[z_from][s_from]->getColor() == WHITE) { //columns can be different if your figure is going to beat another
	    			beat = true;
	    			flag = 1; //white player
	    		}
	    		if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from - 1) && !(NewBoard.board[z_to][s_to]->getPiece() == EMPTY) && NewBoard.board[z_from][s_from]->getColor() == BLACK) { //black player
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
	    		if (!(NewBoard.board[z_to][s_to]->getPiece() == EMPTY) && beat == false) {
	    			return false;
	    		}
	    	}
	    	if (z_to == 7 && NewBoard.board[z_from][s_from]->getColor() == WHITE) {
				cout << "which figure do you want for you pawn?: ";
				newFigure = read_char();
				z = z_to; s = s_to;
				pawn_transformation(NewBoard, newFigure, WHITE, z, s);
				
	    	}
	    	if (z_to == 0 && NewBoard.board[z_from][s_from]->getColor() == BLACK) {
	    		cout << "which figure do you want for you pawn?: ";
	    		newFigure = read_char();
				z = z_to; s = s_to;
				pawn_transformation(NewBoard, newFigure, BLACK, z, s);
	    	}
	    	return true;
        }
};

/*
* class Rook
* derived from Pieces
* added methods:
*   +movement
*/
class Rook: public virtual Piece {
    public:
        Rook() {
            piece = ' ';
            color = NONE;
        }
        Rook(char p, char c) {
            piece = p; color = c;
        }

        /*
        doesnt fit on cpp version yet
        */
        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
            if (NewBoard.board[z_to][s_to]->getColor() == NewBoard.board[z_from][s_from]->getColor()) {
	        	return false;
	        }
	        if (!(z_from == z_to) && !(s_from == s_to)) {
	        	return false;
	        }
	        if ((NewBoard.board[z_to][s_to]->getPiece() != EMPTY && (NewBoard.board[z_to][s_to]->getColor() == NewBoard.board[z_from][s_from]->getColor()))) {
	        	return false;
	        }
	        if (z_from == z_to) {
	        	for (int i = s_from; i < s_to - 1; i++) {
	        		if (NewBoard.board[z_from][i + 1]->getPiece() != EMPTY) {
	        			return false;
	        		}
	        	}
	        }
	        if (s_from == s_to) {
	        	for (int i = z_from; i < z_to - 1; i++) {
	        		if (NewBoard.board[i + 1][s_from]->getPiece() != EMPTY) {
	        			return false;
	        		}
	        	}
	        }
	        return true;
        }
};

/*
* class Knight
* derived from Pieces
* added methods:
*   +movement
*/
class Knight: public Piece {
    public:
        Knight(char p, char c) {
            piece = p; color = c;
        }

        /*
        doesnt fit on cpp version yet
        */
        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
            if (NewBoard.board[z_to][z_from]->getColor() == NewBoard.board[z_from][s_from]->getColor()) {
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
};

/*
* class Pawn
* derived from Pieces
* added methods:
*   +movement
*/
class Bishop: public virtual Piece {
    public:
        Bishop() {
            piece = ' ';
            color = NONE;
        }

        Bishop(char p, char c) {
            piece = p; color = c;
        }

        /*
        doesnt fit on cpp version yet
        */
        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
	        if (NewBoard.board[z_to][s_to]->getColor() == NewBoard.board[z_from][s_from]->getColor()) {
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
	        				if (NewBoard.board[z_from + 1 + i][s_from + 1 + i]->getPiece() != EMPTY) {
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
	        				if (NewBoard.board[z_from + 1 + i][s_from - 1 - i]->getPiece() != EMPTY) {
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
	        				if (NewBoard.board[z_from - 1 + i][s_from + 1 - i]->getPiece() != EMPTY) {
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
	        				if (NewBoard.board[z_from - 1 + i][s_from - 1 + i]->getPiece() != EMPTY) {
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
};

/*
* class King
* derived from Pieces
* added methods:
*   +movement
*/
class King: public Piece {
    public:
        King(char p, char c) {
            piece = p; color = c;
        }

        /*
        doesnt fit on cpp version yet
        */
        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
            if (z_to != z_from + 1 && z_to != z_from - 1 && s_to != s_from + 1 && s_to != s_from - 1) {
		    	return false;
		    }
		    if ((NewBoard.board[z_to][s_to]->getPiece() != EMPTY && (NewBoard.board[z_to][s_to]->getColor() == NewBoard.board[z_from][s_from]->getColor()))) {
		    	return false;
		    }
		    return true;
        }
};

/*
* class Queen
* derived from Rook and Bishop
*/
class Queen: public Rook, public Bishop {
    public:
        Queen() {
            piece = ' ';
            color = NONE;
        }
        Queen(char p, char c) {
            piece = p; color = c;
        }

        /*
        doesnt fit on cpp version yet
        */
        bool movement(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
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
};

/*
* class Board contains:
* attributes:
* - the board on which will be player
* methods:
* + constructor to initilise the board
* + print_board to output the board to commandline
* + getBoard to return the current state of the board to check for moves
* + change_place
* + check 
* + winner
* + change
*/
class Board {
    public:
		Piece *board[fieldsize][fieldsize];
        
        Board() {
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

        void print_board() {
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

		int check(Board NewBoard, int z_from, int z_to, int s_from, int s_to) {
			board[z_from][s_from]->movement(NewBoard, z_from, z_to, s_from, s_to);
        }

		int winner(int z_from, int z_to, int s_from, int s_to) {
			int help;
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

		void change_place(char figure, char c, int z, int s) {
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

		void change(int z_from, int z_to, int s_from, int s_to) {
			change_place(board[z_from][s_from]->getPiece(), board[z_from][s_from]->getColor(), z_to, s_to);
			change_place(EMPTY, NONE, z_from, s_from);
		}

		bool IsEmpty(int z, int s) {
			if (board[z][s]->getPiece() == EMPTY)
	        	return true;
			else
				return false;
		}
        
};

/*
* class Chess contains:
* attributes:
* - the current turn
* methods:
* + gameloop
* + input function
* + check function
*/
class Chess {
    private:
        int turn; //0 is white, 1 is black

    public:
        int input(Board NewBoard, int *z_from, int *z_to, int *s_from, int *s_to) {
			char S_from, S_to;
			do {
            	cout << "which figure do you want to move?: ";
            	cin >> S_from >> *z_from;
	        	if (S_from == '+' && *z_from == 1)
	        		return 11;
	        	if (*z_from < 0 || *z_from > 8 || S_from > 'H' || S_from < 'A')
	        		return 44;
	        	*s_from = S_from - 65; *z_from -= 1;
				if(NewBoard.IsEmpty(*z_from, *s_from))
					return false;
	        	
	        	#if _TURN_ //turn control not compiled if _TURN_ == false
	        		if (amount % 2 == 1 && board[z_from][s_from][1] == black || amount % 2 == 0 && board[z_from][s_from][1] == white) {
	        			return 42;
	        		}
	        	#endif
            	cout << "where do you want to move it to?: ";
            	cin >> S_to >> *z_to;
	        	*s_to = S_to - 65; *z_to -= 1; //convert input in the fitting array-format
			} while(*z_to < 0 || *z_to > 8 || S_to > 'H' || S_to < 'A');
	        return 0;
        }

        int gameloop() {
			int win = 0, z_from, z_to, s_from, s_to;
            Board NewBoard;
			do {
				NewBoard.print_board();
				input(NewBoard, &z_from, &z_to, &s_from, &s_to);
				NewBoard.check(NewBoard, z_from, z_to, s_from, s_to);
				NewBoard.change(z_from, z_to, s_from, s_to);
				win = NewBoard.winner(z_from, z_to, s_from, s_to);
			} while (win == 0);
			return win;
        }
};

int main() {
    Chess NewGame;
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