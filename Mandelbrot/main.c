#include <stdio.h>
#include "iteration.h"
#include <complex.h>
#include <math.h>

#define xLength 100
#define yLength 50

#define amountIterations 1000

#define Black 1
#define White 0

int main() {
    double complex start = 0.1 + 0.1 * I;
    double complex retval = iteration(10, start);

    printf("Start = %lf + j*%lf\n", creal(start), cimag(start));
    printf("Retval = %lf + j*%lf\n", creal(retval), cimag(retval));

    double realStart = -1, realEnd = -1 * realStart, imagStart = realStart, imagEnd = -1 * imagStart;
    double realStep = (fabs(realStart) + fabs(realEnd))/xLength, imagStep = (fabs(imagStart) + fabs(imagEnd))/yLength;
    printf("realStep = %lf, imagStep = %lf\n", realStep, imagStep);

    double rs, is;

    int img[yLength][xLength];

    
    is = imagStart;
    for (int i = 0; i < yLength; i++) {
        rs = realStart;
        for (int k = 0; k < xLength; k++) {
            start = (double)rs + (double)is * I;
            retval = iteration(amountIterations, start);
            if (absSquare(creal(retval), cimag(retval)) < 4.0) {
                img[i][k] = Black;
            } else {
                img[i][k] = White;
            }
            rs += realStep;
        }
        is += imagStep;
    }

    for (int i = 0; i < yLength; i++) {
        for (int k = 0; k < xLength; k++) {
            printf("%i", img[i][k]);
        }
        printf("\n");
    }


    return 0;
}