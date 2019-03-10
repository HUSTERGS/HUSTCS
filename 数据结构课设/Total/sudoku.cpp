#include "sudoku.h"
#include <stdio.h>
#include "dpll.h"
inline int HASH(int i, int j, int n) {
	return n - 1 + 9 * (i - 1) + 9 * 9 * (j - 1) + 1;
}


bool checkDesk(int(*Sudoku)[SUDOKU_LENGTH], int x, int y) {
	int * one_to_nine = (int *)calloc(SUDOKU_LENGTH + 1, sizeof(int));
	// 检查行
	for (int i = 0; i <= y; ++i) {
		if (one_to_nine[Sudoku[x][i]])
		{
			free(one_to_nine);
			one_to_nine = nullptr;
			return false;
		}
		else
			one_to_nine[Sudoku[x][i]]++;
	}
	// 清零
	memset(one_to_nine, 0, sizeof(int)*(SUDOKU_LENGTH + 1));

	// 检查列
	for (int i = 0; i <= x; ++i) {
		if (one_to_nine[Sudoku[i][y]])
		{
			free(one_to_nine);
			one_to_nine = nullptr;
			return false;
		}
		else
			one_to_nine[Sudoku[i][y]]++;
	}

	// 检查九宫格
	memset(one_to_nine, 0, sizeof(int)*(SUDOKU_LENGTH + 1));

	for (int i = (x / 3) * 3; i < (x / 3) * 3 + 3; ++i) {
		for (int j = (y / 3) * 3; j < (y / 3) * 3 + 3; ++j) {
			if (Sudoku[i][j]) {
				if (one_to_nine[Sudoku[i][j]])
				{
					free(one_to_nine);
					one_to_nine = nullptr;
					return false;
				}
				else
					one_to_nine[Sudoku[i][j]]++;
			}
		}
	}
	free(one_to_nine);
	one_to_nine = nullptr;
	return true;
}

bool generate(int(*Sudoku)[SUDOKU_LENGTH], int x, int y) {
	srand((unsigned)time(nullptr));
	Sudoku[x][y] = rand() % 9 + 1;  // 先填入一个随机数字

	bool flag = true;

	for (int i = 0; i < SUDOKU_LENGTH; ++i) {
		// 检查是否满足
		if (flag == false) {
			Sudoku[x][y] = Sudoku[x][y] % 9 + 1;
			flag = true;
		}
		if (!checkDesk(Sudoku, x, y)) {
			// 如果不满足 就尝试+1
			Sudoku[x][y] = Sudoku[x][y] % 9 + 1;
		}
		else {
			if (x == SUDOKU_LENGTH - 1 && y == SUDOKU_LENGTH - 1) {
				// 如果成功并且到达了最后一个,退出
				return true;
			}
			else {
				// 如果成功了，但是没有到最后一个元素，就填写下一个元素
				if (generate(Sudoku, ((y == 8) ? x + 1 : x), (y + 1) % 9))
					return true;
				else if (i < SUDOKU_LENGTH) {
					flag = false;
				}
				else {
					Sudoku[x][y] = 0;
					return false;
				}
			}
		}
	}
	Sudoku[x][y] = 0;
	return false;
}
void loadSudokuFile(int(*a)[SUDOKU_LENGTH]) {
	const char * filename = "sudoku17.txt";
	FILE * fp = fopen(filename, "r");
	for (int i = 0; i < SUDOKU_LENGTH; ++i) {
		for (int j = 0; j < SUDOKU_LENGTH; ++j) {
			a[i][j] = fgetc(fp) - 48;
		}
	}
}

void Reduction(int(*Sudoku)[SUDOKU_LENGTH], const char * filename) {
	//FILE * fp = nullptr;
	FILE * fp = fopen(filename, "w");
	if (!fp) {
		return;
	}
	else {
		// 写注释
		int count = 0;
		for (int i = 0; i < SUDOKU_LENGTH; ++i) {
			fprintf(fp, "c ");
			for (int j = 0; j < SUDOKU_LENGTH; ++j) {
				fprintf(fp, "%d ", Sudoku[i][j]);
				if (Sudoku[i][j])
					count++;
			}
			fprintf(fp, "\n");
		}


		fprintf(fp, "p cnf %d %d\n", SUDOKU_BOX, count + 243 + 2916);

		// 对于每一个已存在的数字
		for (int i = 1; i <= SUDOKU_LENGTH; ++i) {
			for (int j = 1; j <= SUDOKU_LENGTH; ++j) {
				if (Sudoku[i - 1][j - 1]) {
					fprintf(fp, "%d 0\n", HASH(i, j, Sudoku[i - 1][j - 1]));
				}
			}
		}

		// 断言： 每一个单元没有重复的数 2916
		for (int i = 1; i <= SUDOKU_LENGTH; ++i) {
			for (int j = 1; j <= SUDOKU_LENGTH; ++j) {
				for (int n = 1; n <= SUDOKU_LENGTH - 1; ++n) {
					for (int z = n + 1; z <= SUDOKU_LENGTH; ++z) {
						fprintf(fp, "%d %d 0\n", -HASH(i, j, n), -HASH(i, j, z));
					}
				}
			}
		}

		// 断言：每一行包含了每一个数 81
		for (int i = 1; i <= SUDOKU_LENGTH; ++i) {
			for (int n = 1; n <= SUDOKU_LENGTH; ++n) {
				for (int j = 1; j <= SUDOKU_LENGTH; ++j) {
					fprintf(fp, "%d ", HASH(i, j, n));
				}
				fprintf(fp, "0\n");
			}
		}

		// 断言：每一列包含了每一个数 81
		for (int j = 1; j <= SUDOKU_LENGTH; ++j) {
			for (int n = 1; n <= SUDOKU_LENGTH; ++n) {
				for (int i = 1; i <= SUDOKU_LENGTH; ++i) {
					fprintf(fp, "%d ", HASH(i, j, n));
				}
				fprintf(fp, "0\n");
			}
		}

		// 断言： 每一个九宫格包含了一个数 241

		for (int r = 0; r < 3; ++r) {
			for (int s = 0; s < 3; ++s) {
				for (int n = 1; n <= 9; ++n) {
					for (int i = 1; i <= 3; ++i) {
						for (int j = 1; j <= 3; ++j) {
							fprintf(fp, "%d ", HASH(3 * r + i, 3 * s + j, n));
						}
					}
					fprintf(fp, "0\n");
				}
			}
		}
	}
	fclose(fp);
	fp = nullptr;
}

void fillIn(int * resultArray, int(*Sudoku)[SUDOKU_LENGTH]) {
	int temp = 0;
	int i, j, n;
	i = j = n;


	for (int m = 0; m < SUDOKU_BOX; ++m) {
		if (resultArray[m]) {
			temp = m;
			n = temp % SUDOKU_LENGTH;

			temp = (temp - n) / SUDOKU_LENGTH;

			j = temp % SUDOKU_LENGTH;

			temp = temp - j;

			i = temp;

			++n; // n需要额外加1

			Sudoku[i][j] = n;
		}
	}
}

void display(int(*Sudoku)[SUDOKU_LENGTH]) {
	for (int i = 0; i < SUDOKU_LENGTH; ++i) {
		for (int j = 0; j < SUDOKU_LENGTH; ++j) {
			printf("%d ", Sudoku[i][j]);
		}
		printf("\n");
	}
}


void Dig(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName) {
	srand((unsigned)time(nullptr));
	int x = rand() % 9;
	int y = rand() % 9; // 随机生成一个位置
	CNF * cnf = (CNF *)malloc(sizeof(CNF));
	for (int i = 0; i < level; ++i) {
		while (!Sudoku[x][y]) {
			x = rand() % 9;
			y = rand() % 9;
		}
		int temp = Sudoku[x][y];
		for (int i = 0; i < SUDOKU_LENGTH - 1; ++i) {
			cnf = (CNF *)malloc(sizeof(CNF));
			Sudoku[x][y] = (temp + i) % 9 + 1;
			Reduction(Sudoku, tempfileName);
			LoadFile(tempfileName, cnf);
			if (DPLL(cnf)) {
				++i;
				Sudoku[x][y] = temp;
				DestroyCNF(cnf);
				cnf = nullptr;
				break;
			}
			DestroyCNF(cnf);
			cnf = nullptr;
		}
		Sudoku[x][y] = 0;
	}
}

void Dig2(int(*Sudoku)[SUDOKU_LENGTH], int level, const char * tempfileName) {
	srand((unsigned)time(nullptr));
	int x = rand() % 9;
	int y = rand() % 9; // 随机生成一个位置
	CNF * cnf = (CNF *)malloc(sizeof(CNF));
	for (int i = 0; i < level; ++i) {
		while (!Sudoku[x][y]) {
			x = rand() % 9;
			y = rand() % 9;
		}
		Sudoku[x][y] = 0;
	}
}