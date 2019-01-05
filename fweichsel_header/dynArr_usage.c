#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer); //unsave functions can be used this way

#include <stdio.h>
#include <conio.h>
#include "dynArr.h"

void main() {
    //startPointer and endPointer
	//you will need both for your array
    struct list *startPtr, *endPtr;

    //data
	//if you want to store more than 1 data object in the struct you can copy another union in the header file
	//you can either use predefined chars or send them directly:
    //dtype:
	//	mINT = 'i'
	//  mFLOAT = 'f'
	//  mDOUBLE = 'd'
	//  mCHAR = 'c'
	//  mSTRING = 's'
	//  mEMPTY = 'e'
	
	printf("the first data is: \n");
    struct tData myData;
    myData.mdata.intData = 4;
    myData.dtype = mINT;
	//only to show that really the same data is printed out
	printData(myData);

    //init with first data
    init(&startPtr, &endPtr, myData);
	printf("\narray created\n");

	printf("\nthe second data is: \n");
    myData.mdata.charData = 'c';
    myData.dtype = mCHAR;
	printData(myData);

	//append it to the array
    append(&endPtr, myData);
	printf("\nappended second data to the array: \n");

	//print out all Data stored in the array
	printf("\nall the data of the array: \n");
    printAllData(&startPtr, 2);

	//gets the first element of the array and prints it out
	//care 0 is first element, 1 second and so on, like in normal arrays[]
	printf("\nthe first element of the array is: \n");
	struct tData getElementOfArray = getElement(startPtr, 0);
	printData(getElementOfArray);
	//or simply
	//printData(getElement(startPtr, 1));

	//program stays open in the end
	printf("\nclose by pressing anything");
	getch();
    return;
}