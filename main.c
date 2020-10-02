#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int matrix[9][9];

char *removeSpaces(char *buff, int size) {
    for(int i=0; i<255; i++) {
        if(buff[i] == ' ' || buff[i] == '\n') {
            for(int j=i; j<size-1; j++) {
                buff[j] = buff[j+1];
            }
        }
    }
    buff[81] = '\0';
    return buff;
}

bool findUnassignedLocation(int *row, int *col) {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(matrix[i][j] == 0) {
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}

void printPuzzle() {
    printf("---------------------------------------\n");
    for(int i=0; i<9; i++) {
        printf(" | ");
        for(int j=0; j<9; j++) {
            printf(" %d ", matrix[i][j]);

            if((j + 1) % 3 == 0) {
                printf(" | ");
            }
        }
        printf("\n");
        if((i+1) % 3 == 0) {
            printf("---------------------------------------\n");
        }
    }
}

bool possible(int x, int y, int n) {
    int colStart, rowStart;

    if (matrix[y][x] != 0) {
        printf("Error!\n");
        return false;
    }


    for (int i = 0; i < 9; i++) {
        if (matrix[y][i] == n) {
            return false;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (matrix[i][x] == n) {
            return false;
        }
    }

    rowStart = (y/3) * 3;
    colStart = (x/3) * 3;

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(matrix[i + rowStart][j + colStart] == n) {
                return false;
            }
        }
    }

    return true;
}

bool solvePuzzle() {
    int row, col = 0;

    if(!findUnassignedLocation(&row, &col)) {
        printf("\nFinished\n");
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (possible( col, row, num)) {
            matrix[row][col] = num;
            if (solvePuzzle()) {
                return true;
            }
            matrix[row][col] = 0;
        }
    }
    return false;
}

void assignToPuzzleGrid(char *buff) {
    int i = 0;
    int j = 0;
    int k = 0;

    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            matrix[i][j] = buff[k++] - '0';
        }
        if(buff[k] == '\0') {break;}
    }


}

char* getPuzzleFromFile() {
    char c;
    char *buff = malloc(255 * sizeof(char));
    int k = 0;

    FILE *fp = fopen("puzzle.txt", "r");
    if (fp == NULL) {
        printf("U need a puzzle.txt file.\n");
        return NULL;
    };

    while(1) {
        c = fgetc(fp);
        if (c==EOF) {
            break;
        } else {
            buff[k++] = c;
        }
    }


    fclose(fp);
    return buff;
}

int main() {
    char *sudoku;

    sudoku = getPuzzleFromFile();
    sudoku = removeSpaces(sudoku, 255);
    assignToPuzzleGrid(sudoku);

    if (solvePuzzle()) {
        printPuzzle();
    } else {
        printf("\nNo solution or error!\n");
    }

    return 0;
}
