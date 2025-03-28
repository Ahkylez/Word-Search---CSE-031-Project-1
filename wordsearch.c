#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int **path;
int **firstChar;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void cleanInput(char *oldWord) {
    // Iterate until null terminating character and then
    // if the letter is lower case use the way decimal values
    // work and convert the char to capital.
    while (*oldWord != '\0') {
        if (*oldWord >= 97 && *oldWord <= 122) {
            *oldWord = *oldWord - 32;
        }
        oldWord++;
    }
}

void printPuzzle(char** arr) {
    // iterate through 2d array and print properly
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");

}

int findWord(char *word, char** arr, int row, int col, int count, int wordsFound) {
    
    if (*(word + count) == '\0') { // base case
        return 1;
    }

    // Check edges and check if cell is the correct letter
    if (row < 0 || row >= bSize || col < 0 || col >= bSize || *(*(arr + row) + col) != *(word + count)) {
        return 0;
    }

    // Check if overlapping with first character.
    int tempRow = -1;
    int tempCol = -1;

    if (wordsFound > 0){
        for (int i = 0; i < wordsFound; i++){
            tempRow = *(*(firstChar + i) + 0);
            tempCol = *(*(firstChar + i) + 1);

            if (row == tempRow && col == tempCol){
                return 0;
            }
        }
    }

    // checking all adjacent directions
    int found = findWord(word, arr, row - 1, col, count + 1, wordsFound) || findWord(word, arr, row + 1, col, count + 1, wordsFound) ||
                findWord(word, arr, row, col - 1, count + 1, wordsFound) || findWord(word, arr, row, col + 1, count + 1, wordsFound) ||  
                findWord(word, arr, row - 1, col - 1, count + 1, wordsFound) || findWord(word, arr, row - 1, col + 1, count + 1, wordsFound) ||
                findWord(word, arr, row + 1, col - 1, count + 1, wordsFound) || findWord(word, arr, row + 1, col + 1, count + 1, wordsFound);

    // inputing last count first since its below the direction search. 
    if (found){
        if (*(*(path + row) + col) == 0) {
            *(*(path + row) + col) = count + 1;
        } else {   
            *(*(path + row) + col) = *(*(path + row) + col) * 10 + (count + 1); //add numbers to the right of eachother
        }
    }
    
    return found;
}

int numDigits(int n) {   
    int r = 1;
    while (n > 9){
        n = n/10;
        r++;
    }
    return r;
}

void printSearchPath() {
    // use triple nested loop for proper spcaing
    printf("Printing the search path: \n");
    int spaces = 7;
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            spaces = 7 - numDigits(*(*(path + i) + j));
            printf("%d", *(*(path + i) + j));
            for (int k = 0; k < spaces; k++){
                printf(" ");
            }
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, char* word) {
    cleanInput(word);

    // Allocated and initialize the search path 2d array
    path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        *(path + i) = (int*)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++) {
            *(*(path + i) + j) = 0;
        }
    }

    // Allocate space for first character positions
    firstChar = (int**)malloc(bSize * bSize * sizeof(int*)); // Maximum possible matches
    for (int i = 0; i < bSize * bSize; i++) {
        *(firstChar + i) = (int*)malloc(2 * sizeof(int)); // Each match stores (row, col)
    }
    // calling the recursive function for each first letter
    int wordsFound = 0;
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (*(*(arr + i) + j) == *word) {
                if (wordsFound > 0){ // Makes sure the first letter count doesnt overlap with current search path, assuring 1 is always by itself
                    if (*(*(path + i)+j) == 0){
                        if (findWord(word, arr, i, j, 0, wordsFound)) {
                            wordsFound++;
                            if (wordsFound){
                                *(*(firstChar + (wordsFound - 1)) + 0) = i;
                                *(*(firstChar + (wordsFound - 1)) + 1)  = j;
                            }
                        }
                    }
                } 
                else if (findWord(word, arr, i, j, 0, wordsFound)) { // Does the normal search if no words have been found
                    wordsFound++;
                    if (wordsFound){
                        *(*(firstChar + (wordsFound - 1)) + 0) = i;
                        *(*(firstChar + (wordsFound - 1)) + 1)  = j;
                    }
                }
                
            }
        }
    }
    if (wordsFound) {
        printf("Word found!\n");
        printSearchPath();
    } else {
        printf("Word not found\n");
    }

}
