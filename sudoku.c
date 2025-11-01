#include <stdio.h>
#include <stdlib.h>


// data structure to hold a sudoku
struct Sudoku {
    int grid[9][9];     // 9x9 sudoku grid
    // information about which cells are filled
    int rows[9][9];     // which rows are filled with which elements
    int cols[9][9];     // which cols are filled with which elements
    int boxes[9][9];    // which boxes are filled with which elements
    // potential values each cell can store
    int potentials[9][9][9];
};


// get an empty sudoku
struct Sudoku* getSudoku() {
    struct Sudoku *sudoku = (struct Sudoku *) malloc(sizeof(struct Sudoku));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku->grid[i][j] = 0;
            sudoku->rows[i][j] = 0;
            sudoku->cols[i][j] = 0;
            sudoku->boxes[i][j] = 0;

            for (int k = 0; k < 9; k++) {
                sudoku->potentials[i][j][k] = 1;
            }
        }
    }
    return sudoku;
}


// add an element at a location and return 1 if successfully added
int add(struct Sudoku *sudoku, int i, int j, int val) {
    // if the cell is already filled, then the element cannot be added
    if (sudoku->grid[i][j]) return 0;

    // if the element is not in the potentials list, it cannot be added
    if (sudoku->potentials[i][j][val - 1] == 0) return 0;

    int box = 3 * (i / 3) + (j / 3);
    // if the element is already present in the row, column or box, then it cannot be added
    if (sudoku->rows[i][val - 1] || sudoku->cols[j][val - 1] || sudoku->boxes[box][val - 1]) {
        return 0;
    }

    sudoku->grid[i][j] = val;       // set the value

    // update the information
    sudoku->rows[i][val - 1] = 1;
    sudoku->cols[j][val - 1] = 1;
    sudoku->boxes[box][val - 1] = 1;

    // update the potentials for other cells
    for (int k = 0; k < 9; k++) {
        if (val - 1 != k) sudoku->potentials[i][j][k] = 0;
        if (i != k) sudoku->potentials[k][j][val - 1] = 0;
        if (j != k) sudoku->potentials[i][k][val - 1] = 0;
    }
    for (int a = 0; a < 3; a++) {
        int r = 3 * (box / 3) + a;
        for (int b = 0; b < 3; b++) {
            int c = 3 * (box % 3) + b;
            if (r == i && c == j) continue;
            sudoku->potentials[r][c][val - 1] = 0;
        }
    }

    return 1;
}


// if a cell can contain only a single element, places it and returns 0 if invalid
int place(struct Sudoku *sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku->grid[i][j]) continue;

            int potential = -1;
            for (int k = 0; k < 9; k++) {
                if (sudoku->potentials[i][j][k]) {
                    if (potential == -1) potential = k;
                    else {
                        potential = -1;
                        k = 9;
                    }
                }
            }

            if (potential == -1) continue;
            if (!add(sudoku, i, j, potential + 1)) return 0;
        }
    }

    return 1;
}


// if an element can be placed in only a single cell in a row/col/box, place it there
int remaining(struct Sudoku *sudoku) {
    // check for each number
    for (int num = 0; num < 9; num++) {
        for (int i = 0; i < 9; i++) {
            // check each row
            if (sudoku->rows[i][num] == 0) {
                int potential = -1;
                for (int j = 0; j < 9; j++) {
                    if (sudoku->potentials[i][j][num]) {
                        if (potential == -1) potential = j;
                        else {
                            potential = -1;
                            j = 9;
                        }
                    }
                }

                if (potential == -1) continue;
                if (!add(sudoku, i, potential, num + 1)) return 0;
            }
            
            // check each column
            if (sudoku->cols[i][num] == 0) {
                int potential = -1;
                for (int j = 0; j < 9; j++) {
                    if (sudoku->potentials[j][i][num]) {
                        if (potential == -1) potential = j;
                        else {
                            potential = -1;
                            j = 9;
                        }
                    }
                }

                if (potential == -1) continue;
                if (!add(sudoku, potential, i, num + 1)) return 0;
            }

            // check each box
            if (sudoku->boxes[i][num] == 0) {
                int potential = -1;
                for (int j = 0; j < 9; j++) {
                    if (sudoku->potentials[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3][num]) {
                        if (potential == -1) potential = j;
                        else {
                            potential = -1;
                            j = 9;
                        }
                    }
                }

                if (potential == -1) continue;
                if (!add(sudoku, 3 * (i / 3) + potential / 3, 3 * (i % 3) + potential % 3, num + 1)) {
                    return 0;
                }
            }
        }
    }

    return 1;
}


// check if puzzle is solved
int solved(struct Sudoku *sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku->rows[i][j] == 0) return 0;
            if (sudoku->cols[i][j] == 0) return 0;
            if (sudoku->boxes[i][j] == 0) return 0;
        }
    }

    return 1;
}


// brute force for the answer
int bruteForce(struct Sudoku *sudoku, int r, int c) {
    // iterate till end of cells
    for (int a = 9 * r + c; a < 81; a++) {
        int i = a / 9, j = a % 9;

        //look for empty cell
        if (sudoku->grid[i][j]) continue;
        
        // try to find a number to put in cell
        for (int num = 0; num < 9; num++) {
            if (sudoku->rows[i][num] || sudoku->cols[j][num] || sudoku->boxes[3 * (i / 3) + (j / 3)][num]) continue;
            if (sudoku->potentials[i][j][num] == 0) continue;

            sudoku->grid[i][j] = num + 1;       // set num
            // update remaining values
            sudoku->rows[i][num] = 1;
            sudoku->cols[j][num] = 1;
            sudoku->boxes[3 * (i / 3) + (j / 3)][num] = 1;

            // recurse for the rest of the puzzle
            if (bruteForce(sudoku, (j < 8) ? i : i + 1, (j + 1) % 9)) return 1;

            // reset changes
            sudoku->grid[i][j] = 0;
            sudoku->rows[i][num] = 0;
            sudoku->cols[j][num] = 0;
            sudoku->boxes[3 * (i / 3) + (j / 3)][num] = 0;
        }

        return 0;       // if no number could be put, then puzzle is unsolvable
    }

    return 1;           // if reached end, then puzzle is solved
}


// print the sudoku
void print(struct Sudoku *sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) printf("%d", sudoku->grid[i][j]);
        printf("\n");
    }
}


int main() {
    printf("Enter your sudoku. Replace empty spaces with 0\n");
    struct Sudoku *sudoku = getSudoku();            // initialize empty sudoku

    // get input from user
    int r = 0, c = 0;
    char temp;
    while (r < 9) {
        scanf("%c", &temp);
        if (temp < '0' || temp > '9') continue;

        if (temp != '0') {
            if (!add(sudoku, r, c, temp - '0')) {
                printf("\n\n The given sudoku is invalid");
                free(sudoku);
                return 0;
            }
        }

        c++;
        if (c == 9) {
            c = 0;
            r++;
        }
    }
    printf("\n\n");

    // check if already solved
    if (solved(sudoku)) {
        print(sudoku);
        printf("\nDifficulty: 0");
        free(sudoku);
        return 0;
    }

    int difficulty = 0;
    while (difficulty < 5) {
        difficulty++;

        remaining(sudoku);
        place(sudoku);

        if (solved(sudoku)) {
            print(sudoku);
            printf("\nDifficulty: %d", difficulty);
            free(sudoku);
            return 0;
        }
    }

    if (bruteForce(sudoku, 0, 0)) {
        print(sudoku);
        printf("\nDifficulty: 6");
    } else {
        printf("The given sudoku is invalid");
    }

    free(sudoku);
    return 0;
}