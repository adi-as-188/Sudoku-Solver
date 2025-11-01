# Sudoku Solver
A command line based program to automatically solve a given sudoku

## Features
- Solves Sudoku puzzles logically and efficiently
- Implements heuristics for logical solving
- Falls back to brute force if logic isn't enough
- Detects unsolvable/invalid puzzles
- Rates difficulty (1-6)

## Usage
### Compile
```bash
gcc sudoku.c -o sudoku
```
### Run
```
./sudoku
```

### Example input
```
500032000
000700000
004000350
400600000
000250906
700900100
000000000
208500070
003009080
```

### Output
```
517832694
936745812
824196357
459613728
381257946
762984135
145378269
298561473
673429581

Difficulty: 6
```