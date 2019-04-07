#include "dpll.h"
#include "sudoku.h"

int main(int argc, char ** args) {
	/*CNF * cnf = (CNF *)malloc(sizeof(CNF));
	
	assert(cnf != nullptr);
	int type = 0;
	if (argc == 2){
		if (-1 == LoadFile(args[1], cnf)){
			printf("文件不存在\n");
			type = 0;
			return 0;
		}
	}
	
	else {
		type = 1;
		const char * filename = "../SAT测试备选算例/满足算例/S/7cnf20_90000_90000_7.shuffled-20.cnf";
		if (-1 == LoadFile(filename, cnf)){
			printf("文件不存在\n");
			return 0;
		}
	}

	//DisplayData(cnf);
	
	struct timeval start;
	struct timeval end;
	float timer;
	gettimeofday(&start, nullptr);
	DecisionTreeHead * result = DPLL(cnf);
	gettimeofday(&end, nullptr);
	timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;      //计算start和end之间的时间差
	
	if (result) {
		printf("s 1\nv ");
		
		int * resultArray = TurnToArray(result, cnf);  // 最终的结果数组
		PrintArray(resultArray, cnf->varNum + 1);
		printf("\nt  %fms\n",timer * 1000);
		CheckFinalResult(resultArray, cnf);
		if (!type){
			writeFile(resultArray, cnf->varNum + 1, timer, args[1]);
		}
		cnf  = nullptr;	
	}
	else {
		printf("\nt  %fms\n",timer * 1000);
		printf("0\n");
	}
	return 0;*/
	




	int a[SUDOKU_LENGTH][SUDOKU_LENGTH];
	memset(a, 0, SUDOKU_LENGTH * SUDOKU_LENGTH * sizeof(int));
	generate(a, 0, 0);
	//Reduction(a, "terminal.cnf");
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

