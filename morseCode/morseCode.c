#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OUTPUT 1

#define s 's'
#define l 'l'
#define end '\0'

char A[] = {s, l, end};
char B[] = {l, s, s, s, end};
char C[] = {l, s, l, s, end};
char D[] = {l, s, s, end};
char E[] = {s, end};
char F[] = {s, s, l, s, end};
char G[] = {l, l, s, end};
char H[] = {s, s, s, s, end};
char I[] = {s, s, end};
char J[] = {s, l, l, l, end};
char K[] = {l, s, l, end};
char L[] = {s, l, s, s, end};
char M[] = {l, l, end};
char N[] = {l, s, end};
char O[] = {l, l, l, end};
char P[] = {s, l, l, s, end};
char Q[] = {l, l, s, l, end};
char R[] = {s, l, s, end};
char S[] = {s, s, s, end};
char T[] = {l, end};
char U[] = {s, s, l, end};
char V[] = {s, s, s, l, end};
char W[] = {s, l, l, end};
char X[] = {l, s, s, l, end};
char Y[] = {l, s, l, l, end};
char Z[] = {l, l, s, s, end};

char AE[] = {s, l, s, l, end};
char OE[] = {l, l, l, s, end};
char UE[] = {s, s, l, l, end};
char sharpS[] = {s, s, s, l, l, s, s, end};
char CH[] = {l, l, l, l, end};

char QuestionMark[] = {s, s, l, l, s, s, end};
char Period[] = {s, l, s, l, s, l, end};
char Comma[] = {l, l, s, s, l, l, end};

char SOS[] = {s, s, s, l, l, l, s, s, s, end};

//7 units of time nothing between two words
char Space[] = {'P', end};

//3 units of time nothing between letters
char Pause[] = {'p', end};

char Equals[] = {l, s, s, s, l, end};
char Plus[] = {s, l, s, l, s, end};

char N1[] = {s, l, l, l, l, end};
char N2[] = {s, s, l, l, l, end};
char N3[] = {s, s, s, l, l, end};
char N4[] = {s, s, s, s, l, end};
char N5[] = {s, s, s, s, s, end};
char N6[] = {l, s, s, s, s, end};
char N7[] = {l, l, s, s, s, end};
char N8[] = {l, l, l, s, s, end};
char N9[] = {l, l, l, l, s, end};
char N0[] = {l, l, l, l, l, end};

char ** stringToMorse(char *string) {
    int length = strlen(string);//sizeof(string)/sizeof(char);
    if (OUTPUT)
        printf("the length of the string is: %i\n", length);
    char **morseCode = malloc(length * sizeof(char*));
    if (OUTPUT)
        printf("address of allocated memory: %p\n", morseCode);
    for (int i = 0; i < length; i++) {
        if (OUTPUT)
            printf("address of %i-Element is: %p\n", i, *(morseCode + i));
        switch (string[i]) {
            case 'A': *(morseCode + i) = A; break;
            case 'a': *(morseCode + i) = A; break;
            case 'B': *(morseCode + i) = B; break;
            case 'b': *(morseCode + i) = B; break;
            //add 'ch' and 'Ch' here
            case 'C': *(morseCode + i) = C; break;
            case 'c': *(morseCode + i) = C; break;
            case 'D': *(morseCode + i) = D; break;
            case 'd': *(morseCode + i) = D; break;
            case 'E': *(morseCode + i) = E; break;
            case 'e': *(morseCode + i) = E; break;
            case 'F': *(morseCode + i) = F; break;
            case 'f': *(morseCode + i) = F; break;
            case 'G': *(morseCode + i) = G; break;
            case 'g': *(morseCode + i) = G; break;
            case 'H': *(morseCode + i) = H; break;
            case 'h': *(morseCode + i) = H; break;
            case 'I': *(morseCode + i) = I; break;
            case 'i': *(morseCode + i) = I; break;
            case 'J': *(morseCode + i) = J; break;
            case 'j': *(morseCode + i) = J; break;
            case 'K': *(morseCode + i) = K; break;
            case 'k': *(morseCode + i) = K; break;
            case 'L': *(morseCode + i) = L; break;
            case 'l': *(morseCode + i) = L; break;
            case 'M': *(morseCode + i) = M; break;
            case 'm': *(morseCode + i) = M; break;
            case 'N': *(morseCode + i) = N; break;
            case 'n': *(morseCode + i) = N; break;
            case 'O': *(morseCode + i) = O; break;
            case 'o': *(morseCode + i) = O; break;
            case 'P': *(morseCode + i) = P; break;
            case 'p': *(morseCode + i) = P; break;
            case 'Q': *(morseCode + i) = Q; break;
            case 'q': *(morseCode + i) = Q; break;
            case 'R': *(morseCode + i) = R; break;
            case 'r': *(morseCode + i) = R; break;
            case 'S': *(morseCode + i) = S; break;
            case 's': *(morseCode + i) = S; break;
            case 'T': *(morseCode + i) = T; break;
            case 't': *(morseCode + i) = T; break;
            case 'U': *(morseCode + i) = U; break;
            case 'u': *(morseCode + i) = U; break;
            case 'V': *(morseCode + i) = V; break;
            case 'v': *(morseCode + i) = V; break;
            case 'W': *(morseCode + i) = W; break;
            case 'w': *(morseCode + i) = W; break;
            case 'X': *(morseCode + i) = X; break;
            case 'x': *(morseCode + i) = X; break;
            case 'Y': *(morseCode + i) = Y; break;
            case 'y': *(morseCode + i) = Y; break;
            case 'Z': *(morseCode + i) = Z; break;
            case 'z': *(morseCode + i) = Z; break;

            //extended asciiCode
            /*
            //Ä and ä
            case 142: *(morseCode + i) = AE; break;
            case 132: *(morseCode + i) = AE; break;
            //Ö and ö
            case 153: *(morseCode + i) = OE; break;
            case 148: *(morseCode + i) = OE; break;
            //Ü and ü
            case 154: *(morseCode + i) = UE; break;
            case 129: *(morseCode + i) = UE; break;
            //ß
            case 225: *(morseCode + i) = sharpS; break;
            */

            case ' ': *(morseCode + i) = Space; break;
            case '?': *(morseCode + i) = QuestionMark; break;
            case '.': *(morseCode + i) = Period; break;
            case ',': *(morseCode + i) = Comma; break;
            case '=': *(morseCode + i) = Equals; break;
            case '+': *(morseCode + i) = Plus; break;

            case '0': *(morseCode + i) = N0; break;
            case '1': *(morseCode + i) = N1; break;
            case '2': *(morseCode + i) = N2; break;
            case '3': *(morseCode + i) = N3; break;
            case '4': *(morseCode + i) = N4; break;
            case '5': *(morseCode + i) = N5; break;
            case '6': *(morseCode + i) = N6; break;
            case '7': *(morseCode + i) = N7; break;
            case '8': *(morseCode + i) = N8; break;
            case '9': *(morseCode + i) = N9; break;

            case '\0': break;
            
            default: break;
        }
    }
    if (OUTPUT)
        printf("the returned address will be: %p\n", morseCode);
    return morseCode;
}