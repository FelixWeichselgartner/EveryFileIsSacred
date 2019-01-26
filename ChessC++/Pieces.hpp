#ifndef PIECES_HPP_
#define PIECES_HPP_

//Predeklaration of class Board
class Board;

#include "Board.hpp"

/*
* class Piece
* all other pieces are derived of this class
*/
class Piece {
    protected:
        char piece;
        char color;
    
    public:
        Piece();
        Piece(char, char);
		virtual bool movement(Board *, int, int, int, int);
        char getPiece();
        void setPiece(char set);
        char getColor();
        void setColor(char set);
};

/*
* class Rook
* derived from Pieces
* added methods:
*   +movement
*/
class Rook: public virtual Piece {
    public:
        Rook();
        Rook(char, char);
        bool movement(Board *, int, int, int, int);
};

/*
* class Knight
* derived from Pieces
* added methods:
*   +movement
*/
class Knight: public Piece {
    public:
        Knight();
        Knight(char p, char c);
        bool movement(Board *, int, int, int, int);
};

/*
* class Bishop
* derived from Pieces
* added methods:
*   +movement
*/
class Bishop: public virtual Piece {
    public:
        Bishop();
        Bishop(char, char);
        bool movement(Board *, int, int, int, int);
};

/*
* class King
* derived from Pieces
* added methods:
*   +movement
*/
class King: public Piece {
    public:
        King();
        King(char p, char c);
        bool movement(Board *, int, int, int, int);
};

/*
* class Queen
* derived from Rook and Bishop
* added methods:
*   +movement
*/
class Queen: public Rook, public Bishop {
    public:
        Queen();
        Queen(char p, char c);
        bool movement(Board *, int, int, int, int);
};

/*
* class Pawn
* derived from Pieces
* added methods:
*   -read_char
*   +pawn_transformation
*   +movement
*/
class Pawn: public Piece {
    private:
        char read_char();
    public:
        Pawn();
        Pawn(char p, char c);
		void pawn_transformation(Board *, char, char, int, int);
        bool movement(Board *, int, int, int, int);
};

#endif