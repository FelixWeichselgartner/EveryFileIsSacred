/**
 **************************************************************
 * C header for handling linked lists
 **************************************************************
 * Copyright (c) 2019 Felix Weichselgartner
 * all rights reserved
 **************************************************************
 *  original upload to:
 *  https://github.com/FelixWeichselgartner/EveryFileIsSacred
 **************************************************************
 * Date of creating these files: 04.01.2019
 *  Last changes: 05.01.2019
 *  creator: Felix Weichselgartner
 *  purpose: easier memory allocation for
 *           linked lists in C
 **************************************************************
 */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <stdlib.h>

#ifndef DTYPES_1_
#define DTYPES_1_
extern const char mINT, mFLOAT, mDOUBLE, mCHAR, mSTRING, mEMPTY;
#endif

union mData {
    int intData;
    float floatData;
    double doubleData;
    char charData;
    char stringData[32];
};

struct tData {
    union mData mdata;
    char dtype;
};

struct list {
    struct tData tdata;
    int error;
    struct list *previous;
	struct list *next;
};

void printData(struct tData);

void printAllData(struct list **, int);

int init(struct list **, struct list **, struct tData);

int append(struct list **, struct tData);

struct tData getElement(struct list *, int);

void setElement(struct list **, struct tData, int);

int deleteElement(struct list **, struct list **, int);

int deleteAllElements(struct list **, struct list **);

#endif