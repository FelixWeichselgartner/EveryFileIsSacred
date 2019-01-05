#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer); //unsave functions can be used this way

#include <conio.h>
#include "dynMemoryAlloc.h"

//compile commands for gcc: gcc .\USAGE_OF_dynMemoryAlloc.c .\dynMemoryAlloc.c -o .\USAGE_OF_dynMemoryAlloc.exe

void main() {
    //create a pointer for your dynamically allocated array
    //use generateArray to allocate memory
    //iArray for integer Array
    int *iArray;
    generateiArray(&iArray, 3);
    printf("generated integer array\n");

    //give the array some values
    iArray[0] = 5;
    iArray[1] = 10;
    iArray[2] = 1;
    printf("\nadd values\n");

    //print all the data of the array
    printf("\nprint integer array:\n");
    printiArray(iArray, 3);

    //resize the array to 5
    //old data is copied in the new array
    resizeiArray(&iArray, 5);
    printf("\nresized the integer array\n");

    //change and initialise values
    iArray[3] = 15;
    iArray[4] = 314;
    iArray[0] = 271;
    printf("\nnew values\n");

    //print the new array
    printf("\nresized integer array:\n");
    printiArray(iArray, 5);

    //free the heap memory
    free(iArray);
    printf("\nfreed the memory\n");


    //this works similar for other datatypes:
    //prefix:
    //  i for integer
    //  f for float
    //  d for double
    //  c for char
    //  s for string

    printf("\nfloat array:\n");
    float *fArray;
    generatefArray(&fArray, 3);
    for (int i = 0; i < 3; i++)
        fArray[i] = (float)i/7;
    printfArray(fArray, 3);

    //string is a bit tricky
    printf("\nstring array:\n");
    char *sArray;
    generatesArray(&sArray, 3);
    strcpy((sArray), "Hello");
    strcpy((sArray+32), " ");
    strcpy((sArray+2*32), "World!");
    printsArray(sArray, 3);

    //keeps program open in the end
    printf("press any button to close the program");
    getch();
    return;
}