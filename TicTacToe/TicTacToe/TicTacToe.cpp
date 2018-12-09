/*
**************************************************************************
*  TicTacToe Python-script
*  C++-version by Felix
**************************************************************************
*  Copyright on the TicTacToe-logic:
*  Copyright(c) 2018
*		Jakob Lachermeier
*       Felix Weichselgartner
**************************************************************************
* Copyright on SFML software:
* SFML - Copyright (C) 2007-2018 Laurent Gomila - laurent@sfml-dev.org
**************************************************************************
*/

#include <iostream>
using namespace std;
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>

#define window_size 500
#define char_size 128

void delay(int milli_seconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

class TicTacToe {
private:
		bool drawBoard(char board[3][3], sf::RenderWindow * window) {
		sf::Sprite sprite;
		
		sf::Texture Background;
		if (!Background.loadFromFile("TicTacToe_field.png"))
			return EXIT_FAILURE;
		sprite.setPosition(0, 0);
		(*window).draw(sprite);
		

		sf::Texture X, O, EMPTY;
		if (!X.loadFromFile("X.png") || !O.loadFromFile("O.png") || !EMPTY.loadFromFile("EMPTY.png"))
			return EXIT_FAILURE;

		const int n = window_size - 3 * char_size;

		float x, y;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (board[i][k] == 'X') {
					cout << "X";
					sprite.setTexture(X);
				}
				else if (board[i][k] == 'O') {
					cout << "O";
					sprite.setTexture(O);
				}
				else {
					cout << " ";
					sprite.setTexture(EMPTY);;
				}
				switch (k) {
				case 0: x = n + 0; break;
				case 1: x = n + char_size; break;
				case 2: x = n + 2 * char_size; break;
				}
				switch (i) {
				case 0: y = 0; break;
				case 1: y = char_size; break;
				case 2: y = 2 * char_size; break;
				}
				sprite.setPosition(x, y);
				sprite.setScale(1, 1);
				(*window).draw(sprite);
			}
		}
		return EXIT_SUCCESS;
	}

	void showBoard(char board[3][3]) {
		cout << "  1 2 3" << endl;
		cout << "1 " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
		cout << "2 " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
		cout << "3 " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
		cout << "  A B C" << endl;
	}

	bool check(char board[3][3], int z, int s) {
		if (board[z][s] == ' ')
			return true;
		return false;
	}

	void console_input(char board[3][3], char player, int *z, int *s) {
		cout << "it's " << player << "'s turn" << endl;
		cin >> *z >> *s;
		(*z)--; (*s)--;
	}

	void gui_input(char board[3][3], char player, int *z, int *s) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			*z = 0;
			cout << *z;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			*z = 1;
			cout << *z;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			*z = 2;
			cout << *z;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			*s = 0;
			cout << *s;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			*s = 1;
			cout << *s;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			*s = 2;
			cout << *s;
		}
		delay(50);
	}

	void input(char board[3][3], int *turn, int *z, int *s) {
		//x begins, O follows

		char player;
		if (*turn % 2 == 0) {
			player = 'X';
		}
		else {
			player = 'O';
		}

		gui_input(board, player, z, s);

		if (*z<=2 && *z>=0 && *s>=0 && *s<=2) {
			cout << *z << *s;
			if (check(board, *z, *s)) {
				cout << player;
				board[*z][*s] = player;
				cout << *z << *s;
				*z = *s = 4;
				(*turn)++;
			}
		}
	}

	char winner(char board[3][3], int turn) {
		char winner = NULL;
		for (int x = 0; x < 3; x++) {
			if (board[x][0] == board[x][1] == board[x][2] && board[x][0] != ' ') {
				if (board[x][0] == 'X') {
					winner = 'X';
				}
				else {
					winner = 'O';
				}
			}
		}
		for (int x = 0; x < 3; x++) {
			if (board[0][x] == board[1][x] == board[2][x] && board[0][x] != ' ') {
				if (board[0][x] == 'X') {
					winner = 'X';
				}
				else {
					winner = 'O';
				}
			}
		}
		if (board[0][0] == board[1][1] == board[2][2] && board[1][1] != ' ') {
			if (board[1][1] == 'X') {
				winner = 'X';
			}
			else {
				winner = 'O';
			}
		}
		if (board[0][2] == board[1][1] == board[2][0] && board[1][1] != ' ') {
			if (board[1][1] == 'X') {
				winner = 'X';
			}
			else {
				winner = 'O';
			}
		}
		if (winner == NULL && turn == 9) {
			winner = 't';
		}
		return winner;
	}

	void output(char board[3][3] ,sf::RenderWindow * window) {
		(*window).clear(sf::Color::White);
		//(*window).clear();
		showBoard(board);
		drawBoard(board, window);
		(*window).display();
	}

public:
	bool gameloop() {
		sf::RenderWindow window(sf::VideoMode(window_size, window_size), "TicTacToe");
		sf::Event event;

		char board[3][3] = { ' ', ' ', ' ',
							 ' ', ' ', ' ',
							 ' ', ' ', ' ' };
		
		char test_board[3][3] = { 'X', ' ', 'O',
								  'X', ' ', 'O',
								  ' ', 'X', ' ' };

		int turn = 0, z = 4, s = 4;

		while (window.isOpen() && !winner(board, turn)) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			output(board, &window);
			input(board, &turn, &z, &s);
		}
		output(board, &window);
		if (winner(board, turn) == 't') {
			cout << "the game ended in a tie" << endl;
		}
		else {
			cout << "the winner is " << winner(board, turn) << "!" << endl;
		}
		return true;
	}
};

int main() {
	class TicTacToe newGame;
	newGame.gameloop();
	return 0;
}