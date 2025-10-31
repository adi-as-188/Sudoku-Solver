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
            sudoku->rows[i][j] = 0;
            sudoku->cols[i][j] = 0;
            sudoku->boxes[i][j] = 0;

            for (int k = 0; i < 9; k++) {
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
    if (sudoku->potentials[i][j][val] == 0) return 0;

    int box = 3 * (i / 3) + (j / 3);
    // if the element is already present in the row, column or box, then it cannot be added
    if (sudoku->rows[i][val] || sudoku->cols[j][val] || sudoku->boxes[box][val]) {
        return 0;
    }

    sudoku->grid[i][j] = val;       // set the value

    // update the information
    sudoku->rows[i][val] = 1;
    sudoku->cols[j][val] = 1;
    sudoku->boxes[box][val] = 1;

    // update the potentials for other cells
    for (int k = 0; k < 9; k++) {
        if (val != k) sudoku->potentials[i][j][k] = 0;
        if (i != k) sudoku->potentials[k][j][val] = 0;
        if (j != k) sudoku->potentials[i][k][val] = 0;
    }
    for (int a = 0; a < 3; a++) {
        int r = box / 3 + a;
        for (int b = 0; b < 3; b++) {
            int c = box % 3 + b;
            if (r == i && c == b) continue;
            sudoku->potentials[r][c][val] = 0;
        }
    }

    return 1;
}