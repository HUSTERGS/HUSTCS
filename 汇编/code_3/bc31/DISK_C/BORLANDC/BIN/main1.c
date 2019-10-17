#include <stdio.h>
#include <stdlib.h>
#pragma inline

extern void fuction1(void);
extern void fuction2(void);
extern void fuction3(void);
extern void fuction4(void);
extern void fuction5(void);
extern void login(void);
extern char is_boss;
int is_exit = 0;


void printMenu(void);

int main(void){
	int choice;
	while(!is_exit) {
		asm push ds
		login();
		printf("%d\n", is_boss);
		asm pop ds
		printf("%d\n", is_boss);
		//printf("lualla");
		//printf("%d", is_boss);
		if (is_exit){
			return 0;
		}
		printMenu();
		scanf("%d", &choice);
		if (!is_boss){
			switch (choice)
			{
			case 1:
				// asm push ds
				fuction1();
				// asm pop ds
				//printf("lulala");
				//printf("\n");
				break;
			case 6:
				is_exit = 1;
				
				break;
			default:
				break;
			}
		}else {
			switch (choice) {
			case 1: 
				fuction1();
				break;
			case 2:
				
				fuction2();
				break;
			case 3:
				
				fuction3();
				break;
			case 4:
				fuction4();
				break;
			case 5:
				fuction5();
				break;
			case 6:
				is_exit = 1;
				break;
			}
		}
		
	}
	return 0;
}

void printMenu(void){
	if (!is_boss){
		printf("\nPlease choose your action\n");
		printf("1. search\n");
		printf("6. exit\n");
	}else {
		printf("\nPlease choose your action\n");
		printf("1. search\n");
		printf("2. edit\n");
		printf("3. calculate\n");
		printf("4. rank\n");
		printf("5. print all goods\n");
		printf("6. exit\n");
	}
}


