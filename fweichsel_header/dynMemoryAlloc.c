#include <stdio.h>
#include <stdlib.h>

//integer

int generateiArray(int **ptr, int size) {
    *ptr= malloc(size * sizeof(int));
	if (ptr == NULL) {
		printf("No memory could be allocated\n");
		return 0;
	}

	return 1;
}

int resizeiArray(int **ptr, int newSize) {
    *ptr = (int *)realloc(*ptr, newSize * sizeof(int));
    if (ptr == NULL) {
        printf("No memory could be allocated\n");
        return 0;
    }
    return 1;
}

void printiArray(int *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%i] = %i\n", i, ptr[i]);
    }
    return;
}

//float

int generatefArray(float **ptr, int size) {
    *ptr= malloc(size * sizeof(float));
	if (ptr == NULL) {
		printf("No memory could be allocated\n");
		return 0;
	}

	return 1;
}

int resizefArray(float **ptr, int newSize) {
    *ptr = (float *)realloc(*ptr, newSize * sizeof(float));
    if (ptr == NULL) {
        printf("No memory could be allocated\n");
        return 0;
    }
    return 1;
}

void printfArray(float *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%i] = %f\n", i, ptr[i]);
    }
    return;
}

//double

int generatedArray(double **ptr, int size) {
    *ptr= malloc(size * sizeof(double));
	if (ptr == NULL) {
		printf("No memory could be allocated\n");
		return 0;
	}

	return 1;
}

int resizedArray(double **ptr, int newSize) {
    *ptr = (double *)realloc(*ptr, newSize * sizeof(double));
    if (ptr == NULL) {
        printf("No memory could be allocated\n");
        return 0;
    }
    return 1;
}

void printdArray(double *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%i] = %d\n", i, ptr[i]);
    }
    return;
}

//char

int generatecArray(char **ptr, int size) {
    *ptr= malloc(size * sizeof(char));
	if (ptr == NULL) {
		printf("No memory could be allocated\n");
		return 0;
	}

	return 1;
}

int resizecArray(char **ptr, int newSize) {
    *ptr = (char *)realloc(*ptr, newSize * sizeof(char));
    if (ptr == NULL) {
        printf("No memory could be allocated\n");
        return 0;
    }
    return 1;
}

void printcArray(char *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%i] = %c\n", i, ptr[i]);
    }
    return;
}

//string

int generatesArray(char **ptr, int size) {
    *ptr= (char *)malloc(size * 32 * sizeof(char));
	if (ptr == NULL) {
		printf("No memory could be allocated\n");
		return 0;
	}

	return 1;
}

int resizesArray(char **ptr, int newSize) {
    *ptr = (char *)realloc(*ptr, newSize * 32 * sizeof(char));
    if (ptr == NULL) {
        printf("No memory could be allocated\n");
        return 0;
    }
    return 1;
}

void printsArray(char *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%i] = ", i);
        for (int k = 0; k < 32; k++) {
            if (ptr[k + i*32] == '\0')
                break;
            printf("%c", ptr[k + i*32]);
        }
        printf("\n");
    }
    return;
}