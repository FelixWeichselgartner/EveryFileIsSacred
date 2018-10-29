/*
********************************************
*  c-header with basic functions
********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
********************************************
*/

to include the header follow the following instructions:

- copy the files "fweichsel.h" and "fweichsel.c" in the same folder, where the file you want to compile is

- include the header in your c-program with:
	
	#include "fweichsel.h"

- if you compile with "GCC, the GNU Compiler Collection" (https://gcc.gnu.org/):

	gcc -o example example.c fweichsel.c
	
- execute with:

	Linux
	./example

	Windows
	example
	
further information on the functions included:

	Bubblesort: just the basic bubblesort algorithm
		your first argument has to be a pointer on an integer_array
		second argument is the length of the array
	void bubblesort_up(int *, int);
	void bubblesort_down(int *, int);

	XOR-Encoding:
		your first argument is the text you want to encode
		the second argument is the key you want to encode with
		the third argument is the a pointer on the text for the encoding
	void XOR(char *, char *, char *);

	Read-functions:
		first argument is the lowest integer possible
		second argument is the highest integer possible
	int read_int(int, int, int);
		first argument is the lowest character possible
		second argument is the highest character possible
	char read_char(char, char);
		argument is a pointer on a character-array
	void read_string(char *);
	
	Fibonacci:
		returns the n-element of the 1-1-(start-parameter)-fibonacci
	int fibonacci(int);
	
	Integration
		first argument is the lower border
		second argument is the higher border
		third argument is the amout of integratoin parts
		your function has to be declared as f()
	float integrate(float, float, int);
	
	Bisection-Algorithm:
		returns the value of a root if you know there is one in between xL and xR
		returns NAN if theres no root
		xL is the left x value, xR the right one
	float bisection(float xL, float xR)
	
	Average of 2 numbers:
		x is first, y second number
	float ArithM(float x, float y);
	float GeoM(float x, float y);
	float HarmM(float x, float y);
	
	Euklid-Algorith
		returns the biggest divider of a and b
	int euklid_algorithm(int a, int b)
	
	Ohm-parallel resistors:
		returns the resistance of 2 parallel resistors
	float parallel(float a, float b)
	
	solution for quadratic equations:
		parameters:		1. a; 2. b; 3. c; 4. x1; 5. x2;
	void quadratic_equation(float, float, float, float, float);
	
	absolute:
		n is the value -> returns the absolute of n
	int absolute(int n)