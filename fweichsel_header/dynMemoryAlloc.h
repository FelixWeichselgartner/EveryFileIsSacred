/**
 **************************************************************
 * C header for handling dynamical arrays
 **************************************************************
 * Copyright (c) 2019 Felix Weichselgartner
 * all rights reserved
 **************************************************************
 *  original upload to:
 *  https://github.com/FelixWeichselgartner/EveryFileIsSacred
 **************************************************************
 * Date of creating these files: 05.01.2019
 *  Last changes: 05.01.2019
 *  creator: Felix Weichselgartner
 *  purpose: easier memory allocation for
 *           dynamical arrays in C
 **************************************************************
 */

#ifndef DYN_MEMORY_ALLOC_
#define DYN_MEMORY_ALLOC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//integer

int generateiArray(int **, int);

int resizeiArray(int **, int);

void printiArray(int *, int);

//float

int generatefArray(float **, int);

int resizefArray(float **, int);

void printfArray(float *, int);

//double

int generatedArray(double **, int);

int resizedArray(double **, int);

void printdArray(double *, int);

//char

int generatecArray(char **, int);

int resizecArray(char **, int);

void printcArray(char *, int);

//string

int generatesArray(char **, int);

int resizesArray(char **, int);

void printsArray(char *, int);

#endif