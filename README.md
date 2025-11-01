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
5 1 7 | 8 3 2 | 6 9 4
9 3 6 | 7 4 5 | 8 1 2
8 2 4 | 1 9 6 | 3 5 7
------+-------+------
4 5 9 | 6 1 3 | 7 2 8
3 8 1 | 2 5 7 | 9 4 6 
7 6 2 | 9 8 4 | 1 3 5
------+-------+------
1 4 5 | 3 7 8 | 2 6 9
2 9 8 | 5 6 1 | 4 7 3 
6 7 3 | 4 2 9 | 5 8 1

Difficulty: Expert
```