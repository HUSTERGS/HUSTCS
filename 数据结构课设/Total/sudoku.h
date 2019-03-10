#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _SUDOKU_H
#define _SUDOKU_H

#define SUDOKU_LENGTH 9
#define SUDOKU_BOX 729

inline int HASH(int i, int j, int n);
bool checkDesk(int(*Sudoku)[SUDOKU_LENGTH], int x, int y);
bool generate(int(*Sudoku)[SUDOKU_LENGTH], int x, int y);
void loadSudokuFile(int(*a)[SUDOKU_LENGTH]);
void Reduction(int(*Sudoku)[SUDOKU_LENGTH], const char * filename);
void fillIn(int * resultArray, int(*Sudoku)[SUDOKU_LENGTH]);
void display(int(*Sudoku)[SUDOKU_LENGTH]);
void Dig(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName);
void Dig2(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName);
#endif // !_SUDOKU_H
