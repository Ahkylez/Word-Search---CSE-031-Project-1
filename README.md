# Word Search Solver (C Assembly Project)

## Overview
This project implements a **word search puzzle solver** in C, originally designed for an assembly programming course. The solver efficiently finds words in a grid by searching adjacent letters in all possible directions. The project focuses on **pointer manipulation, algorithmic efficiency, and low-level memory handling**, avoiding array notation and external libraries for character conversion.

## Features
- **Efficient Word Search Algorithm**: Implements a depth-first search (DFS)-based approach to locate words.
- **Pointer-Based Memory Manipulation**: Uses dynamic memory allocation and pointer arithmetic instead of array indexing.
- **Backtracking & Path Reconstruction**: Ensures valid paths through adjacency constraints.
- **Case-Insensitive Matching**: Manually implements character case conversion without library functions.
- **Strict Output Formatting**: Produces structured search paths adhering to the project specifications.

## Skills Demonstrated
This project showcases several key skills relevant to software engineering and quantitative finance roles:

- **Algorithm Design & Optimization**: Implements a recursive search algorithm, akin to optimization problems in finance.
- **Low-Level Memory Management**: Direct pointer manipulation demonstrates a deep understanding of C and systems programming.
- **Data Structures**: Efficient use of 2D grids and path tracking, applicable to financial modeling techniques.
- **Precision & Attention to Detail**: Strict adherence to output formatting parallels the precision required in quantitative analysis.
- **Problem Solving & Debugging**: Developing a robust search function mirrors the analytical skills used in quant finance.

## How to Run
1. **Compile the Program**:
   ```sh
   gcc -o wordsearch wordsearch.c
   ```
2. **Run the Program**:
   ```sh
   ./wordsearch puzzle.txt
   ```
3. **Enter the Word to Search**:
   - The program reads a puzzle grid from a file and searches for a user-inputted word.
   - The output displays the grid and the search path if the word is found.

## Example Output
```
Enter the word to search: HELLO

Printing puzzle before search:
W E B M O
I L H L L
M L Z E L
M Y E K O
A O A B A

Word found!
Printing the search path:
0  0  0  0  5
0  0  1  3  4
0  0  0  2  0
0  0  0  0  0
0  0  0  0  0
```
