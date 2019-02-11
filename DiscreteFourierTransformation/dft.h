#ifndef DFT_H_
#define DFT_H_

#include <complex.h>

double arctan2(double, double);

double angle(double complex);

void dft(double *, int, double complex *);

void fft(double *, int, double complex *);

void zeroPadding(double *, int, int);

void zeroPaddingToNextPOW2N(double *, int);

double * hamming(int);

#endif