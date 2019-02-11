#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define pi 3.14159265358979323846

double arctan2(double x, double y) {
    //values = ]-pi;pi]
    if (x>0) {
        return atan(y/x);
    } else if (x<0) {
        if (y>0)
            return atan(y/x)+pi;
        } else if (y==0) {
            return pi
        } else if (y<0) {
            return atan(y/x)-pi;
        }
    } else if (x==0) {
        if (y==0) {
            return 0; //or None actually it has no phase here but 0 is fine
        } else if (y>0) {
            return pi/2;
        } else if (y<0) {
            return -pi/2;
        }
    }
}

double angle(double complex X){
    return arctan2(creal(X), cimag(X))
}

void dft(double *x, int N, double complex *X) {
    X = malloc(N * sizeof(double complex));
    double complex wExponent = 1*I*(-2)*pi/(N)
    double complex temp;
    for (int l = 0; l < N; l++) {
        temp = 0
        for (int k = 0; k < N; k++) {
            temp = x[k]*exp(wExponent*k*l) + temp
        }
        X[l] = temp/N
    }
}

void fft(double *x, int N, double complex *X) {
    int max = N/2;

    //decimation in time
    double *xs = malloc(max * sizeof(double));
    double *xss = malloc(max * sizeof(double));

    for (int k = 0; k < max; k++) {
        xs[k] = x[2*k];
        xss[k] = x[2*k + 1];
    }

    //fourier transform those both parts
    double *XS, *XSS, *X;
    dft(xs, max, XS);
    dft(xss, max, XSS);

    //add both together to actual fourier transformation
    X = malloc(N * sizeof(double complex));
    complex double wExponent = 1*I*2*pi/N*(-1);

    for (int l = 0; l < max; l++) {
        X[l] = (XS[l] + exp(wExponent*l)*XSS[l])/2;
    }

    l = 0
    for (int l = 0; l < max; l++) {
        X[l + max] = (XS[l] - exp(wExponent*l)*XSS[l])/2;
    }
    free(xs); free(xss); free(XS); free(XSS);
}

void zeroPadding(double *function, int N, int n) {
    function = (double *)realloc(function, n * sizeof(double));
    for (int x = n - N; x < n; x++) {
        function[x] = 0; 
    }
}

void zeroPaddingToNextPOW2N(double *function, int N) {
    int n = 1;
    while (N > pow(2, n)) {
        n++;
    }
    int add = pow(2, n) - N
    zeroPadding(function, add, N);
}

double * vonHann(double alpha, double beta, int N) {
    double *vonHann = malloc(N * sizeof(double));
    for (int n = 0; n < N; n++) {
        vonHann[n] = alpha - beta * cos(2 * pi * n / (N - 1))
    }
    return vonHann;
}

double * hamming(int N) {
    double alpha = 25.0/46;
    double beta = 1 - alpha;
    return vonHann(alpha, beta , N);
}