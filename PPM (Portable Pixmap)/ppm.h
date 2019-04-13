#ifndef PPM_H_
#define PPM_H_

#define FILENAME_LENGTH     255
#define EXTENSION_LENGTH      5     // (.ppm == 4 char) + (\0) == 5

#define SUCCESS 1
#define FAILED -1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct ppm_header {
    int width;
    int height;
    int max_color_value;
};

struct ppm_file {
    FILE *fp;
    struct ppm_header header;
    struct rgb* data;
};

void set_ppm_header(struct ppm_header* header, int w, int h, int c) {
    header->width = w;
    header->height = h;
    header->max_color_value = c;
}

void write_ppm_header(FILE* f, struct ppm_header* h) {
    char identifier[] = "P6 ";
    char *whc;
    size_t sz;

    sz = snprintf(NULL, 0, "%d %d %d", h->width, h->height, h->max_color_value);
    whc = (char *)malloc(((int)sz + 1) * sizeof(char));
    if (whc != NULL) {
        snprintf(whc, sz+1, "%d %d %d", h->width, h->height, h->max_color_value);
    } else {
        printf("[Error]> Unable to reserve memory for ppm write.\n");
        exit(1);
    }

    fwrite(identifier, sizeof(char), strlen(identifier), f);
    fwrite(whc, sizeof(char), strlen(whc), f);
}

void write_ppm_data(FILE *f, struct ppm_file* file) {
    fwrite(file->data, sizeof(struct rgb), file->header.width * file->header.height, f);
}

struct ppm_file* init_ppm_file(char* n, int w, int h, int c) {
    struct ppm_file* file = (struct ppm_file*)malloc(sizeof(struct ppm_file));
    char filename[FILENAME_LENGTH];

    if (strlen(n) > FILENAME_LENGTH - EXTENSION_LENGTH || c > 255 || c < 0) {
        printf("[Error]> Filename too long or color value false.\n");
        return NULL;
    } 
    
    strcpy(filename, n);
    strcat(filename, ".ppm");
    file->fp = fopen(filename, "wb");
    if (file->fp == NULL) {
        printf("[Error]> Unable to reserve memory for file pointer.\n");
        return NULL;
    }
    
    set_ppm_header(&file->header, w, h, c);
    file->data = (struct rgb*)calloc(w * h, sizeof(struct rgb));
    if (file->data == NULL) {
        printf("[Error]> Unable to reserve memory for data (rgb values).\n");
    }
    return file;
}

void write_ppm_file(struct ppm_file* f) {
    write_ppm_header(f->fp, &f->header);
    write_ppm_data(f->fp, f);
}

void close_ppm_file(struct ppm_file* f) {
    free(f->data);
    fclose(f->fp);
    free(f);
}

#endif