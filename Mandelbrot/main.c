#include <stdio.h>
#include <stdint.h>
#include "iteration.h"
#include <complex.h>
#include <math.h>
#include <time.h>
//https://github.com/marc-q/libbmp
#include "libbmp-master/libbmp.h"

#define xLength 1000
#define yLength 1400

#define amountIterations 5000

#define Black 0
#define White 1

#define BMP_IMG 1

struct Colors {
    int8_t colors[yLength][xLength];
};

int main() {
    time_t startt = time(0);

    double realStart = -1.5, realEnd = 0.4, imagStart = realStart, imagEnd = -1 * imagStart;
    double realStep = (fabs(realStart) + fabs(realEnd))/xLength, imagStep = (fabs(imagStart) + fabs(imagEnd))/yLength;
    printf("realStep = %lf, imagStep = %lf\n", realStep, imagStep);

    double rs, is;
    double complex start, retval;
    int LoopColor = 0;

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
            LoopColor = iteration(amountIterations, start);
            img.colors[i][k] = LoopColor;
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
            switch(img.colors[i][k]) {
                case 0: bmp_pixel_init (&MyImg.img_pixels[i][k], 0, 0, 0); break;
                case 1: bmp_pixel_init (&MyImg.img_pixels[i][k], 255, 255, 255); break;
                case 2: bmp_pixel_init (&MyImg.img_pixels[i][k], 255, 0, 0); break;
                case 3: bmp_pixel_init (&MyImg.img_pixels[i][k], 0, 255, 0); break;
                case 4: bmp_pixel_init (&MyImg.img_pixels[i][k], 0, 0, 255); break;
            }
        }
    }
    bmp_img_write (&MyImg, "Mandelbrot.bmp");
	bmp_img_free (&MyImg);
    #endif

    printf("The amount of time needed to calculate Mandelbrot: %lf seconds" ,(double)difftime(time(0), startt));

    return 0;
}