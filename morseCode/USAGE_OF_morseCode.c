#include <stdio.h>
#include "morseCode.h"
#include <string.h>

//compile command for gcc
//gcc .\USAGE_OF_morseCode.c .\morseCode.c -o .\USAGE_OF_morseCode.exe

void main() {
    char *name = "Felix on Github\0";
	printf("the original string is %s\n", name);
    char **morseName = stringToMorse(name);
    printf("returned address is: %p\n", morseName);
    char *temp;
    for (int i = 0; i < strlen(name); i++) {
        temp = *(morseName + i);
        printf("address of the %i-Element is: %p\n", i, temp);
        printf("content: %s\n", temp);
    }
}