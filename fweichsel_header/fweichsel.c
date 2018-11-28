/*
********************************************
*  c-header with basic functions
********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
********************************************
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h> 

const double pi = 3.141592653589;
const double e = 2.718281828459;

void bubblesort_up(int *array, int length) {
	int i, j, tmp;
	for (i = length - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (array[j] > array[j + 1]) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}

void bubblesort_down(int *array, int length) {
	int i, j, tmp;
	for (i = length - 1; i > 0; i--)
	{
			for (j = 0; j < i; j++)
		{
				if (array[j] < array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}

void XOR(char *origin, char *key, char *output) {
	int n = 0;
	for (int i = 0; i < strlen(origin); i++) {
		if (n == strlen(key)) {
			n = 0;
		}
		if (origin[i] == key[n]) {
			output[i] = origin[i];
		}
		else {
			output[i] = origin[i] ^ key[n];
		}
		n++;
	}
}

int read_int(int a, int b) {
	int z;
	do {
		printf("enter an integer [%i; %i]: ", a, b);
		scanf("%i", &z);
		while (getchar() != '\n');
	} while (z < a && z > b);
	return z;
}

float read_float(float a, float b) {
	float z;
		do {
			printf("enter a float number [%f; %f]: ", a, b);
			scanf("%f", &z);
			while (getchar() != '\n');
		} while (z < a && z > b);
		return z;
}

double read_double(double a, double b) {
	double z;
		do {
			printf("enter a double number [%lf; %lf]: ", a, b);
			scanf("%lf", &z);
			while (getchar() != '\n');
		} while (z < a && z > b);
		return z;
}

char read_char(char a, char b) {
	char c;
	do {
		printf("enter a character [%c; %c]: ", a, b);
		scanf("%c", &c);
		while (getchar() != '\n');
	} while (c < a && c > b);
	return c;
}

void read_string(char *string) {
	printf("enter a string: ");
	gets(string);
}

void read_string_scanf(char *string); {
	printf("enter a string: ";)
	scanf("%[^\n]s", string);
}

int fibonacci(int n) {
	if (n <= 1)
		return n;
	return fibonacci(n-1) + fibonacci(n-2);
}

#ifndef F_(X)_
#define F_(X)_
float f(int x) {
	return exp(x);
}
#endif

float integrate(float a, float b, int n) {
	float delta = (float)(b - a) / n, erg = 0;
	for (float x = a; x < b; x += delta) {
		erg+=f(x)*delta;
	}
	return erg;
}

float bisection(float xL, float xR) {
	float yR, yL, xLPruef, Backup;
	do {
	int n=0;
	if (n=1)
		printf("Error");
		return NAN;
	n++;
	yR=f(xR);
	yL=f(xL);
	} while (yR*yL>0);
	
	while (xL!=xR) {
		do {
			Backup = xL;
			xL = (xL+xR)/2;
			yR=f(xR);
			yL=f(xL);
		} while (yL*yR<0);
		if (xL==xR) {
			return xL;
		}
		else {
			xR=xL;
			xL=Backup;
		}
	}
}

float ArithM(float x, float y) {
	return (float) 0.5*(x + y);
}

float GeoM(float x, float y) {
	return (float) sqrt(x*y);
}

float HarmM(float x, float y) {
	return (float) (2 * x*y) / (x+y);
}

int euklid_algorithm(int a1, int b1) {
	int a=a1, b=b1;
	while (a!=b) {
		if (a>b) {
				a=a-b;
			}
		else {
				b=b-a;
			}
	}
	return a;
}

float parallel(float a, float b) {
	return (a*b)/(a+b);
}

void quadratic_formula(float a, float b, float c, float *x1, float *x2)	{
	if (a==0) {
		if (b==0) {
			printf("parallel to x-axes");
		}
		else {
			*x1=-c/b;
			printf("the root is at x=%f", *x1);
		}
	}
	else {
		if (b*b-4*a*c<0) {
			printf("only complex solutions for this equation");
		}
		else {
			if (b*b-4*a*c == 0) {
				*x1=-b/2*a;
				printf("there's a double root at x=%f", *x1);
			}
			else {
				*x1=(-b-sqrt(b*b-4*a*c))/2*a;
				*x2=(-b+sqrt(b*b-4*a*c))/2*a;
				printf("the roots are x1=%f and x2=%f", *x1, *x2);
			}
		}
	}
}

int absolute(int x) {
	if (x >= 0)
		return x;
	else return -x;
}

void delay(int milli_seconds) {
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) 
        ; 
} 