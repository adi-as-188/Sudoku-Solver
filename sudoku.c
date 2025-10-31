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