#ifndef SUDOKU_H
#define SUDOKU_H

#include "basic.h"

#define SUDOKU_LENGTH 9
#define SUDOKU_BOX 729


inline int HASH(int i, int j, int n);
void fillIn(int * resultArray, int(*Sudoku)[SUDOKU_LENGTH]);
void printSudoku(int(*Sudoku)[SUDOKU_LENGTH]);
bool checkDesk(int(*Sudoku)[SUDOKU_LENGTH], int x, int y);
bool generate(int(*Sudoku)[SUDOKU_LENGTH], int x, int y);
void Reduction(int(*Sudoku)[SUDOKU_LENGTH], const char * filename);
void display(int(*Sudoku)[SUDOKU_LENGTH]);
void Dig(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName);
void Dig2(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName);
#endif // !SUDOKU_H

