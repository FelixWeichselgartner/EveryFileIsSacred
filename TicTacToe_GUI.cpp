/*
****************************************************************************************************
*  TicTacToe Python-script
*  C++-version by Felix
****************************************************************************************************
*  Copyright on the TicTacToe-logic:
*  Copyright(c) 2018
*		Jakob Lachermeier
*       Felix Weichselgartner
****************************************************************************************************
* Copyright on SFML software:
* SFML - Copyright (C) 2007-2018 Laurent Gomila - laurent@sfml-dev.org
****************************************************************************************************
* Copyright on fonts:
* Copyright 2010-2018 Adobe (http://www.adobe.com/), with Reserved Font Name 'Source'. 
* All Rights Reserved. Source is a trademark of Adobe in the United States and/or other countries.
* This Font Software is licensed under the SIL Open Font License, Version 1.1.
****************************************************************************************************
*/

#include <iostream>
using namespace std;
#include <string>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>

#define window_size 500
#define char_size 128
const int x_offset = window_size - 3 * char_size;
const int y_offset = 30;

void delay(int milli_seconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

class TicTacToe {
private:
	int z, s, turn;
	char board[3][3];
	char pwinner;

private:
	bool drawBoard(sf::RenderWindow * window) {
		cout << pwinner;
		sf::Font font;
		if (!font.loadFromFile("fonts/SourceSansPro-Light.ttf"))
			return EXIT_FAILURE;
		string top, add, space = " "; char S;
		if (pwinner == 'n') {
			if (z == 4 && s == 4) {
				top = "Current input: Row:    Columns:   ";
			}
			else if (z == 4 && s != 4) {
				S = 65 + s;
				//does somehow not work without space
				top = "Current input: Row: " + space + " Columns: " + S;
			}
			else if (s == 4 && z != 4) {
				top = "Current input: Row: " + to_string(z + 1) + " Columns:   ";
			}
			else {
				S = 65 + s;
				top = "Current input: Row: " + to_string(z + 1) + " Columns: " + S;
			}
		}
		else if (pwinner == 'X') {
			top = "The winner is X";
		}
		else if (pwinner == 'O') {
			top = "The winner is O";
		}
		else if (pwinner == 't') {
			top = "The game ended in a tie";
		}
		sf::Text text(top, font, 25);
		text.setPosition(0, 0);
		text.setFillColor(sf::Color::Black);
		(*window).draw(text);

		float x, y;

		sf::Sprite sprite;
		
		sf::Texture Background;
		if (!Background.loadFromFile("field.png"))
			return EXIT_FAILURE;
		sprite.setPosition(0, y_offset);
		sprite.setTexture(Background);
		(*window).draw(sprite);

		sf::Texture X, O, EMPTY;
		if (!X.loadFromFile("X.png") || !O.loadFromFile("O.png") || !EMPTY.loadFromFile("EMPTY.png"))
			return EXIT_FAILURE;

		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (board[i][k] == 'X') {
					sprite.setTexture(X);
				}
				else if (board[i][k] == 'O') {
					sprite.setTexture(O);
				}
				else {
					sprite.setTexture(EMPTY);;
				}
				switch (k) {
				case 0: x = x_offset + 0; break;
				case 1: x = x_offset + char_size; break;
				case 2: x = x_offset + 2 * char_size; break;
				}
				switch (i) {
				case 0: y = y_offset + 0; break;
				case 1: y = y_offset + char_size; break;
				case 2: y = y_offset + 2 * char_size; break;
				}
				sprite.setPosition(x, y);
				sprite.setScale(1, 1);
				(*window).draw(sprite);
			}
		}
		return EXIT_SUCCESS;
	}

	void showBoard() {
		cout << "  1 2 3" << endl;
		cout << "1 " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
		cout << "2 " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
		cout << "3 " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
		cout << "  A B C" << endl;
	}

	bool check(int z, int s, bool *enable) {
		if (board[z][s] == ' ')
			return true;
		*enable = false;
		return false;
	}

	void console_input(char player, int *z, int *s) {
		cout << "it's " << player << "'s turn" << endl;
		cin >> *z >> *s;
		(*z)--; (*s)--;
	}

	void gui_input(char player, bool *enable) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			z = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			z = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			z = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			s = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			s = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			s = 2;
		}
		if ((z <= 2 && z >= 0 && s >= 0 && s <= 2) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			*enable = true;
			delay(150);
		}
		delay(50);
	}

	void input(bool *enable) {
		//x begins, O follows

		char player;
		if (turn % 2 == 0) {
			player = 'X';
		}
		else {
			player = 'O';
		}

		gui_input(player, enable);

		if (z <= 2 && z >= 0 && s >= 0 && s <= 2 && *enable == true) {
			if (check(z, s, enable)) {
				board[z][s] = player;
				z = s = 4;
				*enable = false;
				(turn)++;
			}
		}
	}

	char winner() {
		if (pwinner != 't') {
			for (int x = 0; x < 3; x++) {
				if (board[x][0] == board[x][1] && board[x][1] == board[x][2] && board[x][0] != ' ') {
					if (board[x][0] == 'X') {
						pwinner = 'X';
					}
					else {
						pwinner = 'O';
					}
				}
			}
			for (int x = 0; x < 3; x++) {
				if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[0][x] != ' ') {
					if (board[0][x] == 'X') {
						pwinner = 'X';
					}
					else {
						pwinner = 'O';
					}
				}
			}
			if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ') {
				if (board[1][1] == 'X') {
					pwinner = 'X';
				}
				else {
					pwinner = 'O';
				}
			}
			if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
				if (board[1][1] == 'X') {
					pwinner = 'X';
				}
				else {
					pwinner = 'O';
				}
			}
			if (pwinner == 'n' && turn == 9) {
				pwinner = 't';
			}
		}
		return pwinner;
	}

	void output(sf::RenderWindow * window) {
		(*window).clear(sf::Color::White);
		drawBoard(window);
		(*window).display();
	}

public:
	TicTacToe() {
		turn = 0; z = s = 4;
		pwinner = 'n';
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				board[i][k] = ' ';
			}
		}
	}

	bool gameloop() {
		sf::RenderWindow window(sf::VideoMode(window_size, window_size + y_offset), "TicTacToe");
		sf::Event event;

		bool enable = false;

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (winner() == 'n') {
				input(&enable);
			}
			else if (winner() == 't') {
				cout << "the game ended in a tie" << endl;
			}
			else {
				cout << "the winner is " << pwinner << "!" << endl;
			}
			output(&window);
		}
		return true;
	}
};

int main() {
	class TicTacToe newGame;
	newGame.gameloop();
	return 0;
}