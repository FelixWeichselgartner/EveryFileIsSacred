#include "ppm.h"

void main() {
    int width = 150, height = 150, color = 255;
    struct ppm_file* img = init_ppm_file("testfile", width, height, color);
    uint8_t red = 255, green = 255/2, blue = 0;
    for (int i = 0; i < height * width; i++) {
        img->data[i].r = red;
        img->data[i].g = green;
        img->data[i].b = blue;
        red++;
        green++;
        blue++;
    }
    write_ppm_file(img);
    close_ppm_file(img);
    return;
}