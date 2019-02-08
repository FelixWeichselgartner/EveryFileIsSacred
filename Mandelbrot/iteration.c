#include <complex.h>
#include <stdio.h>

double absSquare(double x, double y) {
    return x*x + y*y;
}

double complex iteration(int n, double complex point) {
    double complex retval = 0 + 0 * I;
    for (int i = 0; i < n; i++) {
        retval = retval * retval + point;
        if (absSquare(creal(retval), cimag(retval)) > 4.0)
            break;
    }
    return retval;
}