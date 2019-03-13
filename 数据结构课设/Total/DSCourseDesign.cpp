#include "dpll.h"
#include "sudoku.h"
int main(int argc, char ** args) {
	/*CNF * cnf = (CNF *)malloc(sizeof(CNF));

	assert(cnf != nullptr);

	if (argc == 2)
		LoadFile(args[1], cnf);
	else {
		const char * filename = "hai.cnf";
		LoadFile(filename, cnf);
	}

	//DisplayData(cnf);
	clock_t startTime = clock();
	DecisionTreeHead * result = DPLL(cnf);
	clock_t endTime = clock();
	int duration = (int)(endTime - startTime);
	printf("DPLL time: %d ms\n", duration);
	if (result) {
		//DisplayResult(result);
		int * resultArray = TurnToArray(result, cnf);  // 最终的结果数组



		//fillIn(resultArray, a);
		//printSudoku(a);
		PrintArray(resultArray, cnf->varNum + 1);
		CheckFinalResult(resultArray, cnf);
	}
	else {
		printf("failed\n");
	}
	return 0;*/
	
	int a[SUDOKU_LENGTH][SUDOKU_LENGTH];
	memset(a, 0, SUDOKU_LENGTH * SUDOKU_LENGTH * sizeof(int));
	generate(a, 0, 0);
	Reduction(a, "terminal.cnf");
	Dig2(a, 40, "lulala.cnf");
	display(a);
	Reduction(a, "hai.cnf");
	CNF * cnf = (CNF *)malloc(sizeof(CNF));
	LoadFile("hai.cnf", cnf);
	clock_t startTime = clock();
	DecisionTreeHead * result = DPLL(cnf);
	clock_t endTime = clock();
	int duration = (int)(endTime - startTime);
	if (result) {
		int * resultArray = TurnToArray(result, cnf);  // 最终的结果数组

		printf("DPLL time: %d ms\n", duration);

		fillIn(resultArray, a);
		display(a);
		//PrintArray(resultArray, cnf->varNum + 1);
		CheckFinalResult(resultArray, cnf);
	}
	return 0;
}

