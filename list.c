#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// A function that initializes the call list
CallList initialize(int maxSize) {
        CallList *newList = malloc(sizeof(CallList));
        newList->currentSize = 0;
        newList->maxSize = maxSize;
        newList->entries = malloc(sizeof(int) * maxSize);
        return *newList;
}

// A function that adds an element to the call list, if it is not at full capacity
int add(int item, CallList *list) {
        if (list->currentSize < list->maxSize) {
                list->entries[list->currentSize] = item;
                list->currentSize = list->currentSize + 1;
        }
        else {
                printf("Maximum capacity of the call list has been reached\n");
                exit(6);
        }
        return item;
}

// A function that prints out the call list
void print(CallList list) {
        int i;
        for (i = 0; i < list.maxSize; i++) {
                int temp = list.entries[i];
                if (list.entries[i] == 0) {
                        break;
                }
                else {
                        if (1 <= temp && temp <= 9) {
                                printf("L0%1d ", temp);
                        }
                        else if (10 <= temp && temp <= 15) {
                                printf("L%d ", temp);
                        }
                        else if (16 <= temp && temp <= 30) {
                                printf("I%d ", temp);
                        }
                        else if (31 <= temp && temp <= 45) {
                                printf("N%d ", temp);
                        }
                        else if (46 <= temp && temp <= 60) {
                                printf("U%d ", temp);
                        }
                        else {
                                printf("X%d ", temp);
                        }
                }
        }
}
