/*
***********************************************
*  C - Chess program
***********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
***********************************************
*/

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer); //scanf can be used this way
#include <stdio.h>
#include <math.h>
#include <string.h>
#define fieldsize 8
#define background_color "color C0"
#define white_color "\x1B[37m" //this only works on win10 -> win7 version to come
#define black_color "\x1B[0m" //same as above
const char neutral = '0', white = '1', black = '2';
#define true 1
#define false 0
#define _TURN_ false //false: turn is not checked
#define _ENCODE_ false //false: save file is not encoded
#define _CHECK_ true //false: figure-movement are not checked
const char encode_figure = 'S';
const char encode_color = 'W';

/*
* things to fix:
*	can't swap the king and the rook (rochade)
*	checkmated isn't printed out
*	check is not printed out
*/

/*
* reads a char for the pawn-transformation
* possible options are:
*		German: D, T, L, S
*		English: Q, R, B, K
*/

char read_char() {
	char c;
	do {
		scanf("%c", &c);
		while (getchar() != '\n');
	} while (c != 'T' && c != 'S' && c != 'L' && c != 'D');
	return c;
}

/*
* returns the absolute value of n
*/

int absolute(int n) {
	if (n >= 0) {
		return n;
	}
	if (n < 0) {
		return (-n);
	}
}

/*
* ables you to check for infinit loop
*/

void test() {
	printf("no infinit loop until here\n");
}

/*
* @param char board is the board to initialize
*/

void setup(char board[fieldsize][fieldsize][2]) {
	for (int k = 0; k < fieldsize; k++) {
		for (int i = 0; i < fieldsize; i++) {
			board[k][i][0] = ' ';
			board[k][i][1] = neutral;
		}
	}
	/*
	* Bauer B = Pawn P
	* König K = King K
	* Läufer L = Bishop B
	* Springer S = Knight K
	* Turm T = Rook R
	* Dame D = Queen Q
	*/
	board[0][0][0] = board[0][7][0] = board[7][0][0] = board[7][7][0] = 'T';
	board[0][1][0] = board[0][6][0] = board[7][1][0] = board[7][6][0] = 'S';
	board[0][2][0] = board[0][5][0] = board[7][2][0] = board[7][5][0] = 'L';
	board[0][3][0] = board[7][3][0] = 'D';
	board[0][4][0] = board[7][4][0] = 'K';
	board[0][0][1] = board[0][1][1] = board[0][2][1] = board[0][3][1] = white;
	board[0][4][1] = board[0][5][1] = board[0][6][1] = board[0][7][1] = white;
	board[7][0][1] = board[7][1][1] = board[7][2][1] = board[7][3][1] = black;
	board[7][4][1] = board[7][5][1] = board[7][6][1] = board[7][7][1] = black;
	for (int i = 0; i < fieldsize; i++) {
		board[6][i][0] = 'B'; //those 2 as one
		board[6][i][1] = black;
	}
	for (int i = 0; i < fieldsize; i++) {
		board[1][i][0] = 'B';
		board[1][i][1] = white;
	}
}

/*
* prints out the current board to the command line
*/

void show_board(char board[fieldsize][fieldsize][2]) {
	for (int k = 7, l = 8; k >= 0; k--, l--) {
		printf("%s%d| ", black_color, l);
		for (int i = 0; i < fieldsize; i++) {
			if (board[k][i][1] == white)
				printf("%s%c ", white_color, board[k][i][0]);
			else {
				printf("%s%c ", black_color, board[k][i][0]);
			}
		}
		printf("\n");
	}
	printf("%s   ----------------\n   A B C D E F G H\n", black_color);
}

/*
* the bishop movement is checked here
* excluded it in an extra function
* since the queen also uses the bishop movement
*/

int bishop_movement(char figure, char color, char board[fieldsize][fieldsize][2], int s_from, int z_from, int s_to, int z_to) {
	//if (board[z_to][s_to][1] == color) { color is false
	if (board[z_to][s_to][1] == board[z_from][s_from][1]) {
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
					if (board[z_from + 1 + i][s_from + 1 + i][0] != ' ') {
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
					if (board[z_from + 1 + i][s_from - 1 - i][0] != ' ') {
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
					if (board[z_from - 1 + i][s_from + 1 - i][0] != ' ') {
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
					if (board[z_from - 1 + i][s_from - 1 + i][0] != ' ') {
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
* the rook movement is checked here
* excluded it in an extra function
* since the queen also uses the rook movement
*/

int rook_movement(char figure, char color, char board[fieldsize][fieldsize][2], int s_from, int z_from, int s_to, int z_to) {
	if (board[z_to][s_to][1] == color) {
		return false;
	}
	if (!(z_from == z_to) && !(s_from == s_to)) {
		return false;
	}
	if ((board[z_to][s_to][0] != ' ' && (board[z_to][s_to][1] == board[z_from][s_from][1]))) {
		return false;
	}
	if (z_from == z_to) {
		for (int i = s_from; i < s_to - 1; i++) {
			if (board[z_from][i + 1][0] != ' ') {
				return false;
			}
		}
	}
	if (s_from == s_to) {
		for (int i = z_from; i < z_to - 1; i++) {
			if (board[i + 1][s_from][0] != ' ') {
				return false;
			}
		}
	}
	return true;
}

/*
* @param char figure the figure that is moved in that turn
* @param char color the color of the figure
* @param char board the current board
* @param int s_from the column the figure came from
* @param int z_from the row the figure came from
* @param int s_to the column the player wants the figure to go to
* @param int s_from the row the player wants the figure to go to
* @return false if figure is not allowed to move that way
* @return true if figure is allowed to move that way
*/

int check(char figure, char color, char board[fieldsize][fieldsize][2], int s_from, int z_from, int s_to, int z_to) {
	int beat = false, flag = 0;
	if (figure == 'B') { //columns must be the same
		if (s_from != s_to) {
			if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from + 1) && !(board[z_to][s_to][0] == ' ') && board[z_from][s_from][1] == white) { //columns can be different if your figure is going to beat another
				beat = true;
				flag = 1; //white player
			}
			if ((s_from == s_to + 1 || s_from == s_to - 1) && (z_to == z_from - 1) && !(board[z_to][s_to][0] == ' ') && board[z_from][s_from][1] == black) { //black player
				beat = true;
				flag = 1;
			}
			if (flag == 0) {
				return false;
			}
		}
		if (figure == 'B' && color == white) {
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
		if (figure == 'B' && color == black) {
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
			if (!(board[z_to][s_to][0] == ' ') && beat == false) {
				return false;
			}
		}
		if (z_to == 7 && board[z_from][s_from][1] == white) {
			printf("which figure do you want for you pawn?: ");
			board[z_from][s_from][0] = read_char();
		}
		if (z_to == 0 && board[z_from][s_from][1] == black) {
			printf("which figure do you want for you pawn?: ");
			board[z_from][s_from][0] = read_char();
		}
		return true;
	}
	if (figure == 'T') {
		if (rook_movement(board[z_from][s_from][0], board[z_from][s_from][1], board, s_from, z_from, s_to, z_to) == true) {
			return true;
		}
		else {
			return false;
		}
		
	}
	if (figure == 'K') {
		if (z_to != z_from + 1 && z_to != z_from - 1 && s_to != s_from + 1 && s_to != s_from - 1) {
			return false;
		}
		if ((board[z_to][s_to][0] != ' ' && (board[z_to][s_to][1] == board[z_from][s_from][1]))) {
			return false;
		}
		return true;
	}
	if (figure == 'S') {
		if (board[z_to][z_from][1] == color) {
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
	if (figure == 'L') { //checking the bishop
		if (bishop_movement(board[z_from][s_from][0], board[z_from][s_from][1], board, s_from, z_from, s_to, z_to) == true) {
			return true;
		}
		else {
			return false;
		}
	}
	if (figure == 'D') {
		if (z_from != z_to && s_from != s_to) { //bishop movement in here
			if (bishop_movement(board[z_from][s_from][0], board[z_from][s_from][1], board, s_from, z_from, s_to, z_to) == true) {
				return true;
			}
			else {
				return false;
			}
		}
		if (z_from == z_to || s_from == s_to) { //tower movement in here
			if (rook_movement(board[z_from][s_from][0], board[z_from][s_from][1], board, s_from, z_from, s_to, z_to) == true) {
				return true;
			}
			else {
				return false;
			}
		}
		return true;
	}
}

/*
* @param char board the current board
* @param int amount the current turn
* takes 2 command line inputs
* first one specifies the figure to move
* second one specifies where to move it
* @return 1 if white won -1 if black won
*/

int input(char board[fieldsize][fieldsize][2], int amount) {
	int z_from, z_to, s_from, s_to, help = 0;
	char S_from, S_to;
	printf("which figure do you want to move?: ");
	scanf("%c %d", &S_from, &z_from);
	while (getchar() != '\n');
	if (S_from == '+' && z_from == 1)
		return 11;
	if (z_from < 0 || z_from > 8 || S_from > 'H' || S_from < 'A')
		return 44;
	s_from = S_from - 65; z_from -= 1;
	if (board[z_from][s_from][0] == ' ')
		return 45;
	#if _TURN_ //turn control not compiled if _TURN_ == false
		if (amount % 2 == 1 && board[z_from][s_from][1] == black || amount % 2 == 0 && board[z_from][s_from][1] == white) {
			return 42;
		}
	#endif
	printf("where do you want to move it to?: ");
	scanf("%c %d", &S_to, &z_to);
	while (getchar() != '\n');
	if (z_to < 0 || z_to > 8 || S_to > 'H' || S_to < 'A')
		return 44;
	s_to = S_to - 65; z_to -= 1; //convert input in the fitting array-format
	#if _CHECK_ //check function not compiled if _CHECK_ == false
		if ((check(board[z_from][s_from][0], board[z_from][s_from][1], board, s_from, z_from, s_to, z_to)) == false) //checks if figures can move that way
			return 43;
	#endif
	if (board[z_to][s_to][0] == 'K' && board[z_to][s_to][1] == white)
		help = -1;
	if (board[z_to][s_to][0] == 'K' && board[z_to][s_to][1] == black)
		help = 1;
	board[z_to][s_to][0] = board[z_from][s_from][0];
	board[z_to][s_to][1] = board[z_from][s_from][1];
	board[z_from][s_from][0] = ' ';
	board[z_from][s_from][1] = neutral;
	if (help == 1)
		return 1;
	if (help == -1)
		return -1;
	return 0;
}

/*
* @param char board[][][] this board will be saved
*/

void save_game(char board[fieldsize][fieldsize][2], int turn) {
	FILE *fp;
	char name[20];
	printf("how do you want to call your save file?: ");
	gets(name);
	strcat(name, ".chess");
	fp = fopen(name, "w");
	for (int a = fieldsize - 1; a >= 0; a--) {
		for (int b = 0; b < fieldsize; b++) {
			#if _ENCODE_
				fprintf(fp, "%c", board[a][b][0] ^ encode_figure);
			#else
				fprintf(fp, "%c", board[a][b][0]);
			#endif
		}
		fprintf(fp, "\n");
	}
	for (int a = fieldsize - 1; a >= 0; a--) {
		for (int b = 0; b < fieldsize; b++) {
			#if _ENCODE_
				fprintf(fp, "%c", board[a][b][1] ^ encode_color);
			#else
				fprintf(fp, "%c", board[a][b][1]);
			#endif
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "%d", turn);
	fclose(fp);
}

/*
* @param char board[][][] your board in which your save game is loaded
*/

int catch_old(char board[fieldsize][fieldsize][2], int *turn) {
	FILE *fp;
	char name[20], temp;
	int flag = 0;
	printf("whats the name of your save-file?: ");
	gets(name);
	strcat(name, ".chess");
	fp = fopen(name, "r");
	if (fp == NULL) {
		printf("file couldn't be opened\npress any button to close the game\n");
		getchar();
		return 0;
		flag = 1;
	}
	for (int a = fieldsize - 1; a >= 0; a--) {
		for (int b = 0; b < fieldsize; b++) {
			#if _ENCODE_
				temp = fgetc(fp) ^ encode_figure;
			#else
				temp = fgetc(fp);
			#endif
			#if _ENCODE_
				if (temp == ('\n' ^ encode_figure)) {
					board[a][b][0] = fgetc(fp) ^ encode_figure;
				}
				else board[a][b][0] = temp;
			#else
				if (temp == '\n') {
					board[a][b][0] = fgetc(fp);
				}
				else board[a][b][0] = temp;
			#endif
			//printf("this is board[%d][%d][0] = '%c'\n", a, b, board[a][b][0]);
		}
	}
	for (int a = fieldsize - 1; a >= 0; a--) {
		for (int b = 0; b < fieldsize; b++) {
			#if _ENCODE_
				temp = fgetc(fp) ^ encode_color;
			#else
				temp = fgetc(fp);
			#endif
			#if _ENCODE_
				if (temp == ('\n' ^ encode_color)) {
					board[a][b][1] = fgetc(fp) ^ encode_color;
				}
				else board[a][b][1] = temp;
			#else
				if (temp == '\n') {
					board[a][b][1] = fgetc(fp);
				}
				else board[a][b][1] = temp;
			#endif
			//printf("this is board[%d][%d][1] = '%c'\n", a, b, board[a][b][1]);
		}
	}
	*turn = fgetc(fp);
	fclose(fp);
	if (flag != 1) {
		return true;
	}
}

/*
* starts the game loop
*/

void main() {
	char board[fieldsize][fieldsize][2]; //create chess-board
	char new_old;
	int amount = 1, win = 0; //amout of turns; if win is 1 white wins, if win is -1 black wins
	printf("type in 'n' if you want to start a new game\nyou can save by entering '+' and 1 as the position of your figure\ntype in 'o' if you want to load an old game: ");
	scanf("%c", &new_old);
	while (getchar() != '\n');
	if (new_old == 'o') { //load an old game
		int temp = catch_old(board, &amount);
		if(temp == false) {
			return;
		}
		printf("your old board has been loaded\n");
		printf("press any button to begin: ");
		getchar();
		system("cls");
	}
	else if (new_old == 'n') {
		setup(board); //write in board the standard chess layout
		printf("press any button to begin: ");
		getchar();
		system("cls");
	}
	else {
		printf("please restart the game\n");
		getchar();
		return;
	}
	system(background_color); //set the background color to red
	show_board(board); //prints out the array
	while (win != -1 && win != 1) { //checks if somebody won yet
		if (amount == 1) //white begins in the first turn
			printf("white begins\n");
		win = input(board, amount); //player inserts which figure and where
		if (win == 11) {
			save_game(board, amount);
			printf("your game has been saved\n");
			printf("press any button to close the game");
			getchar();
			return;
		}
		if (win == 45) {
			printf("there is no figure to move\n");
			continue;
		}
		if (win == 44) {
			printf("out of board\n");
			continue;
		}
		if (win == 43) {
			printf("your figure can't move that way\n");
			continue;
		}
		#if _TURN_ //turn control not compiled if _TURN_ == false
			if (win == 42) { //e.g. black player is moved in a white players turn
				printf("its not your turn\n");
				continue;
			}
		#endif
		system("cls"); //clears the console
		show_board(board); //prints the board
		printf("%sthis is turn number %d\n", black_color, amount); //prints in which turn you are
		if (win == 1) { //checks if white won
			printf("white wins!\n");
			printf("press any button to close the game");
			getchar();
		}
		if (win == -1) { //checks if black won
			printf("black wins!\n");
			printf("press any button to close the game");
			getchar();
		}
		amount++; //turn is one higher now
	}
}