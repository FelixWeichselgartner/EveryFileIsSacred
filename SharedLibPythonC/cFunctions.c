/*
functions from my own header
https://github.com/FelixWeichselgartner/EveryFileIsSacred/tree/master/fweichsel_header
*/

/*
https://docs.python.org/3/library/ctypes.html

commands to make shared lib:
gcc -m(Num) -c -Wall cFunctions.c
-m64 for 64bit
-m32 (standard) for 32bit
gcc -shared -o libfile.so cFunctions.o
*/

#include <time.h>
#include <math.h>

float ArithM(float x, float y) {
	return (float) 0.5*(x + y);
}

float GeoM(float x, float y) {
	return (float) sqrt(x*y);
}

float HarmM(float x, float y) {
	return (float) (2 * x*y) / (x+y);
}

float parallel(float a, float b) {
	return (a * b)/(a + b);
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

int sum(int a, int b) {
	return a+b;
}