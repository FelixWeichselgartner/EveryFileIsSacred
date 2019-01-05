#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "dynArr.h"

const char mINT = 'i', mFLOAT = 'f', mDOUBLE = 'd', mCHAR = 'c', mSTRING = 's', mEMPTY = 'e';

void printData(struct tData d) {
    if (d.dtype == mINT) {
        printf("int = %d\n", d.mdata.intData);
    } else if (d.dtype == mFLOAT) {
        printf("float = %f\n", d.mdata.floatData);
    } else if (d.dtype == mDOUBLE) {
        printf("double = %lf\n", d.mdata.doubleData);
    } else if (d.dtype == mCHAR) {
        printf("char = %c\n", d.mdata.charData);
    } else if (d.dtype == mSTRING) {
        printf("string = %s\n", d.mdata.stringData);
    } else if (d.dtype == mEMPTY) {
        printf("empty\n");
    } else {
        printf("error occured!\n");
    }
    return;
}

void printAllData(struct list **startPointer, int n) {
    struct list *ptr = *startPointer;
    for (int i = 0; i < n; i++) {
        if (ptr == NULL) {
            return; //NULL for second element
        }
        printf("array[%d] = ", i);
        printData(ptr->tdata);
        ptr = ptr->next;

		//comment later
		//getch();
    }
    return;
}

int firstElement(struct list **startPointer, struct list **endPointer, struct tData d) {
    struct list *ptr;
	if ((ptr = (struct list *)malloc(sizeof(struct list))) == NULL) {
		return 0;
	} else {
		*startPointer = *endPointer = ptr;

		//comment later
		//printf("startPointer = %p, endPointer = %p\n", *startPointer, *endPointer);
		//getch();

		(*startPointer)->previous = NULL;
		(*endPointer)->next = NULL;
		(*startPointer)->error = 0; // == end->error == ptr->error
        ptr->tdata = d;
		return 1;
	}
}

int init (struct list **startPointer, struct list **endPointer, struct tData d) {
	*startPointer = *endPointer = NULL;

	//comment later
	//printf("startPointer = %p, endPointer = %p\n", *startPointer, *endPointer);
	//getch();

    firstElement(startPointer, endPointer, d);

	//comment later
	//printf("startPointer = %p, endPointer = %p\n", *startPointer, *endPointer);
	//getch();

    return 0;
}

int append(struct list **endPointer, struct tData d) {
    struct list *ptr;
	if ((ptr = (struct list *)malloc(sizeof(struct list))) == NULL) {
		return 0;
	} else {
		(*endPointer)->next = ptr;
        ptr->previous = *endPointer;
        ptr->tdata = d;
		ptr->next = NULL;
        (*endPointer) = ptr;
		return 1;
	}
}

struct tData getElement(struct list *startPointer, int n) {
    struct list *ptr = startPointer;
    for (int i = 0; i < n; i++) {
        if (ptr->next == NULL) {
            ptr->error = 1;
            return ptr->tdata;
        } else {
            ptr = ptr->next;
        }
    }
    return ptr->tdata;
}

void setElement(struct list **startPointer, struct tData d, int n) {
    struct list *ptr = *startPointer;
    for (int i = 0; i < n; i++) {
        ptr = ptr->next;
        if (ptr == NULL) {
            return;
        }
    }
    ptr->tdata = d;
    return;
}

int deleteElement(struct list **startPointer, struct list **endPointer, int n) {
	struct list *ptr = *startPointer, *previous = NULL, *next = NULL;

    //search element to delete
	for (int i = 0; i < n; i++) {
        if (ptr == NULL) {
            return 1;
        } else {
            ptr = ptr->next;
        }
    }
    previous = ptr->previous;
    next = ptr->next;
	
    //rearrange pointers
	if (ptr == *startPointer) {
		(*startPointer) = ptr->next;
        (*startPointer)->previous = NULL;
    } else if (ptr == *endPointer) {
        (*endPointer) = ptr->previous;
        (*endPointer)->next = NULL;
    } else {
		previous->next = ptr->next;
        next->previous = ptr->previous;
    }

    //free memory
	free(ptr);
	return 0;
}

int deleteAllElements(struct list **startPointer, struct list **endPointer) {
    while (!deleteElement(startPointer, endPointer, 1)) {
		;
    }
	deleteElement(startPointer, endPointer, 1);
    return 0;
}