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
 * Date of creating these files: 04.01.2019
 *  Last changes: 04.01.2019
 *  creator: Felix Weichselgartner
 *  purpose: easier memory allocation for
 *           dynamical arrays in C
 **************************************************************
 */

#ifndef DYN_ARR_
#define DYN_ARR_

extern const char mINT, mFLOAT, mDOUBLE, mCHAR, mSTRING, mEMPTY;

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