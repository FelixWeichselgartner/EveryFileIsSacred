/*
********************************************
*  c-header with basic functions
********************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
********************************************
*/

#ifndef FWEICHSEL_H_
#define FWEICHSEL_H_

void bubblesort_up(int *, int);
void bubblesort_down(int *, int);
void XOR(char *, char *, char *);
int read_int(int, int);
float read_float(float, float);
double read_double(double, double);
char read_char(char, char);
void read_string(char *);
int fibonacci(int);
float integrate(float, float, int);
float bisection(float, float);
float ArithM(float x, float y);
float GeoM(float x, float y);
float HarmM(float x, float y);
int euklid_algorithm(int, int);
float parallel(float, float);
void quadratic_equation(float, float, float, float, float);
int absolute(int);

#endif