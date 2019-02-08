#include <complex.h>
#include <stdio.h>

int selectColor(int c) {
    switch(c) {
        case 1: return 2;
        case 2: return 3;
        case 3: return 4;
        default: return 1;
    }
}

double absSquare(double x, double y) {
    return x*x + y*y;
}

int iteration(int n, double complex point) {
    double complex retval = 0 + 0 * I;
    for (int i = 0; i < n; i++) {
        retval = retval * retval + point;
        if (absSquare(creal(retval), cimag(retval)) > 4.0) {
            return selectColor(i);
        }
    }
    return 0;
}