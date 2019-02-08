#include <stdio.h>
#include <stdint.h>
#include "iteration.h"
#include <complex.h>
#include <math.h>
#include <time.h>
//https://github.com/marc-q/libbmp
#include "libbmp-master/libbmp.h"

#define xLength 1400
#define yLength 1400

#define amountIterations 5000

#define Black 1
#define White 0

#define BMP_IMG 1

struct Colors {
    int8_t colors[yLength][xLength];
};

int main() {
    time_t startt = time(0);

    double realStart = -1.0, realEnd = 0.4, imagStart = realStart, imagEnd = -1 * imagStart;
    double realStep = (fabs(realStart) + fabs(realEnd))/xLength, imagStep = (fabs(imagStart) + fabs(imagEnd))/yLength;
    printf("realStep = %lf, imagStep = %lf\n", realStep, imagStep);

    double rs, is;
    double complex start, retval;

    #if BMP_IMG
    bmp_img MyImg;
    bmp_img_init_df(&MyImg, xLength, yLength);
    #endif

    struct Colors img;

    
    is = imagStart;
    for (int i = 0; i < yLength; i++) {
        rs = realStart;
        for (int k = 0; k < xLength; k++) {
            start = (double)rs + (double)is * I;
            retval = iteration(amountIterations, start);
            if (absSquare(creal(retval), cimag(retval)) < 4.0) {
                img.colors[i][k] = Black;
            } else {
                img.colors[i][k] = White;
            }
            rs += realStep;
        }
        is += imagStep;
    }

    #if BMP_IMG == 0
    for (int i = 0; i < yLength; i++) {
        for (int k = 0; k < xLength; k++) {
            printf("%i", img[i][k]);
        }
        printf("\n");
    }
    #endif

    #if BMP_IMG
    for (int i = 0; i < yLength; i++) {
        for (int k = 0; k < xLength; k++) {
            if(img.colors[i][k])
                bmp_pixel_init (&MyImg.img_pixels[i][k], 0, 0, 0);
            else
                bmp_pixel_init (&MyImg.img_pixels[i][k], 255, 255, 255);
        }
    }
    bmp_img_write (&MyImg, "Mandelbrot.bmp");
	bmp_img_free (&MyImg);
    #endif

    printf("The amount of time needed to calculate Mandelbrot: %lf seconds" ,(double)difftime(time(0), startt));

    return 0;
}