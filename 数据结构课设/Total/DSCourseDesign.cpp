#include "dpll.h"
#include "sudoku.h"
#include <unistd.h>
#include <getopt.h>

struct options
{
    int p;  // 命令行参数，表示打印内部表示
    int s;	// 命令行参数，表示是否保存文件
    const char * filename; // 命令行参数，用于输入文件名
}option;

int main(int argc, char ** argv) {
	int opt;
	option.s = 0;
	option.p = 0;
	option.filename = nullptr;
	while ((opt = getopt(argc, argv, "spf:")) != -1) {
            if (opt == 's')
                option.s = 1;
            else if (opt == 'p')
                option.p = 1;
            else if (opt == 'f')
                option.filename = optarg;
	}

	CNF * cnf = (CNF *)malloc(sizeof(CNF));
	
	assert(cnf != nullptr);
	if (option.filename != nullptr){
		if (-1 == LoadFile(option.filename, cnf)){
			printf("文件不存在\n");
			return 0;
		}
	}
	
	else {
		printf("请以 -f filename 输入文件路径\n");
		return 0;
	}
	if (option.p){
		DisplayData(cnf);
	}
	
	
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
		if (option.s){
			writeFile(resultArray, cnf->varNum + 1, timer, option.filename);
		}
		cnf  = nullptr;	
	}
	else {
		printf("\nt  %fms\n",timer * 1000);
		printf("0\n");
	}
	return 0;
}

