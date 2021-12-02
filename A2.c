#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"

// Function Prototypes
void checkFileReadableExists(char * inputFile);
int numberOfLines(char * inputFile);
int numberOfValues(char * inputFile);
void readNumbers(char * inputFile, int * data);
void initializeMarked(int * marked);
void checkMiddleValue(int * data, char * inputFile);
void checkDuplicates(int * data, char * inputFile);
void checkColumnRanges(int * data, char * inputFile);
void printData(int * data, int * marked);
void printGame(int * data, int * marked, CallList list);
void printGameNext(int * data, int * marked, CallList list);
void generateRandomNumber(int * data, int * marked, CallList * list);
int winCheck(int * data, int * marked);

int main(int argc, char *argv[]) {
        // If the user does not pass in two arguments, then exit(1)
        if (argc != 3) {
                fprintf(stderr, "Usage: %s seed cardFile\n", argv[0]);
                exit(1);
        }
        // If the seed is not an integer, then exit(2)
        if (!atoi(argv[1])) {
                fprintf(stderr, "Expected integer seed, but got %s\n", argv[1]);
                exit(2);
        }
        checkFileReadableExists(argv[2]);
        int lineCount = numberOfLines(argv[2]);
        if (lineCount != 5) {
                fprintf(stderr, "%s has bad format\n", argv[2]);
                exit(4);
        }
        int numVals = numberOfValues(argv[2]);
        if (numVals != 25) {
                fprintf(stderr, "%s has bad format\n", argv[2]);
                exit(4);
        }
        int data[25];
        int marked[75];
        initializeMarked(marked);
        readNumbers(argv[2], data);
        checkMiddleValue(data, argv[2]);
        checkDuplicates(data, argv[2]);
        checkColumnRanges(data, argv[2]);
        CallList list = initialize(75);
        int seedNumber = atoi(argv[1]);
        srand(seedNumber);
        printGame(data, marked, list);
        char str[75];
        char c;
        int result;
        while(1) {
                str[0] = '\0';
                scanf("%[^\n]", str);
                scanf("%*c");
                if (strlen(str) == 0) {
                  printGame(data, marked, list);
                }
                for (int i = 0; i < strlen(str); i++) {
                        if (str[i] != 'q') {
                                generateRandomNumber(data, marked, &list);
                                putchar('\n');
                                printGame(data, marked, list);
                                if (winCheck(data, marked) == 1) {
                                        printf("\nWINNER\n");
                                        exit(0);
                                }
                        }
                        else {
                                c = str[i];
                                break;
                        }
                }
                if (c == 'q') {
                        exit(0);
                }
        }
        return 0;
}

/*
   - Prints out the format for the game
   - Clears the screen each time the function is called
*/
void printGame(int * data, int * marked, CallList list) {
        system("clear");
        printf("CallList: ");
        print(list);
        printf("\n");
        printf("L   I   N   U   X   \n");
        printData(data, marked);
        printf("enter any non-enter key for Call (q to quit): ");
}

/* 
   - Generates a random number (from 1 to 75) by passing the seed
   - 75 is the maximum number of elements we can (no duplicates)
   - Adds the generated random number to the call list
   - Repeatedly asks the user for input, until they enter 'q' or reach the capacity: 75
*/
void generateRandomNumber(int * data, int * marked, CallList * list) {
        int temp;
        char c;
        temp = (rand() % 75) + 1;
        if (marked[temp] == 0) {
                add(temp, list);
                marked[temp] = 1;
        }
        else {
                generateRandomNumber(data, marked, list);
        }
}

/* 
   - Checks if an input-file is readable, and if it exists
   - If the input-file is not readable or DNE, exit the program
*/
void checkFileReadableExists(char * inputFile) {
        FILE *fp;
        if ((fp = fopen(inputFile, "r")) == NULL) {
                fprintf(stderr,"%s not readable or doesn't exist\n", inputFile);
                exit(3);
        }
}
/* 
   - Counts and returns the number of lines from the input-file
   - May be redundant b/c of the numberOfValues function
*/
int numberOfLines(char * inputFile) {
        int lineCount = 0;
        char c;
        FILE *fp;
        fp = fopen(inputFile, "r");
        while ((c = getc(fp)) != EOF) {
                if (c == '\n') {
                        lineCount++;
                }
        }
        return lineCount;
}

/*
   - Counts and returns the number of values from the input-file
*/
int numberOfValues(char * inputFile) {
        int numVals = 0;
        FILE *fp;
        fp = fopen(inputFile, "r");
        char c;
        while ((c = getc(fp)) != EOF) {
                if ((c == ' ') || (c == '\n')) {
                        numVals++;
                }
        }
        return numVals;
}

/*
   - Reads numbers from an input-file into an array
*/
void readNumbers(char * inputFile, int * data) {
        FILE *fp;
        fp = fopen(inputFile, "r");
        int i;
        for (i = 0; i < 25; i++) {
                fscanf(fp, "%2d", &data[i]);
        }
}

/*
   - Initializes an array of marked numbers, which all have
     an initial value of 0
*/
void initializeMarked(int * marked) {
        int i;
        for (i = 0; i < 75; i++) {
                marked[i] = 0;
        }
        marked[0] = 1;
}

/*
   - Checks if the middle value of the input-file is 00
*/
void checkMiddleValue(int * data, char * inputFile) {
        if (data[12] != 0) {
                fprintf(stderr, "%s has bad format\n", inputFile);
                exit(4);
        }
}

/*
   - Checks if the input-file contains duplicates
*/
void checkDuplicates(int * data, char * inputFile) {
        int i, j, size = 25;
        for (i = 0; i < size; i++)
        {
                for (j = i + 1; j < size; j++) {
                        if (data[i] == data[j]) {
                                fprintf(stderr, "%s has bad format\n", inputFile);
                                exit(4);
                        }
                }
        }
}

/*
   - Checks if the column ranges for the input-file are valid
*/
void checkColumnRanges(int * data, char * inputFile) {
        int i, temp, size = 25;
        for (i = 0; i < size; i += 5) {
                temp = data[i];
                if (1 <= temp && temp <= 15) {
                        continue;
                }
                else {
                        fprintf(stderr, "%s has bad format\n", inputFile);
                        exit(4);
                }
        }
        for (i = 1; i < size; i += 5) {
                temp = data[i];
                if (16 <= temp && temp <= 30) {
                        continue;
                }
                else {
                        fprintf(stderr, "%s has bad format\n", inputFile);
                        exit(4);
                }
        }
        for (i = 2; i < size; i += 5) {
                temp = data[i];
                if (31 <= temp && temp <= 45 || temp == 0) {
                        continue;
                }
                else {
                        fprintf(stderr, "%s has bad format\n", inputFile);
                        exit(4);
                }
        }
        for (i = 3; i < size; i += 5) {
                temp = data[i];
                if (46 <= temp && temp <= 60) {
                        continue;
                }
                else {
                        fprintf(stderr, "%s has bad format\n", inputFile);
                        exit(4);
                }
        }
        for (i = 4; i < size; i += 5) {
                temp = data[i];
                if (61 <= temp && temp <= 75) {
                        continue;
                }
                else {
                        fprintf(stderr, "%s has bad format\n", inputFile);
                        exit(4);
                }
        }
}

/*
   - Prints the entries in the data array, in the appropriate format
   - If the data is marked, print the value and add 'm'
   - If the data is not marked, then just print out the value
*/
void printData(int * data, int * marked) {
        int i, temp;
        for (i = 0; i < 25; i++) {
                temp = data[i];
                if (marked[temp] == 1) {
                        if (i == 4 || i == 9 || i == 14 || i == 19 || i == 24) {
                                if (data[i] <= 9) {
                                        printf("0%1dm\n", data[i]);
                                }
                                else {
                                        printf("%2dm\n", data[i]);
                                }
                        }
                        else {
                                if (data[i] <= 9) {
                                        printf("0%1dm ", data[i]);
                                }
                                else {
                                        printf("%2dm ", data[i]);
                                }
                        }
                }
                else {
                        if (i == 4 || i == 9 || i == 14 || i == 19 || i == 24) {
                                if (data[i] <= 9) {
                                        printf("0%1d\n", data[i]);
                                }
                                else {
                                        printf("%2d\n", data[i]);
                                }
                        }
                        else {
                                if (data[i] <= 9) {
                                        printf("0%1d  ", data[i]);
                                }
                                else {
                                        printf("%2d  ", data[i]);
                                }
                        }
                }
        }
}

/*
   - Checks if the user wins the game
*/
int winCheck(int * data, int * marked) {
        int i, temp, temp1, temp2, temp3, temp4;

        // Check if the four corners are marked
        int corner1 = data[0], corner2 = data[4], corner3 = data[19], corner4 = data[24];
        if (marked[corner1] == 1 && marked[corner2] == 1 && marked[corner3] == 1 && marked[corner4] == 1) {
                return 1;
        }

        // Check if a row is marked
        for (i = 0; i < 25; i += 5) {
                temp = data[i];
                temp1 = data[i + 1];
                temp2 = data[i + 2];
                temp3 = data[i + 3];
                temp4 = data[i + 4];
                if (marked[temp] == 1 && marked[temp1] == 1 && marked[temp2] == 1 && marked[temp3] == 1
                    && marked[temp4] == 1) {
                        return 1;
                }
        }

        // Check if a column is marked
        for (i = 0; i < 5; i++) {
                temp = data[i];
                temp1 = data[i + 5];
                temp2 = data[i + 10];
                temp3 = data[i + 15];
                temp4 = data[i + 20];
                if (marked[temp] == 1 && marked[temp1] == 1 && marked[temp2] == 1 && marked[temp3] == 1
                   && marked[temp4] == 1) {
                        return 1;
                }
        }
}

