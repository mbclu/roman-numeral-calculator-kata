#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "src/calculator.h"

void printUsage() {
	printf("Usage:\n");
	printf("\t1.) enter the first Roman Numeral and press return\n");
	printf("\t2.) enter an operation (either `+` or `-`) and press return\n");
	printf("\t3.) enter a second Roman Numeral and press return\n");
}

void signal_catch_interrupts(int signal) {
	printf("Invalid input received. Please run the program again.\n");
}

int main() {
	char *firstInput = malloc(30);
	char operator;
	char *secondInput = malloc(30);
	char *result;
	
	printUsage();
	
	scanf(" %s", firstInput);
	getchar();
	scanf(" %c", &operator);
	getchar();
	scanf(" %s", secondInput);
	
	int ret;

    ret = signal(SIGINT, signal_catch_interrupts);

    if(ret == SIG_ERR) {
		printf("Error: unable to set signal handler.\n");
		exit(0);
	}
   
	if ('+' == operator) {
		result = add(firstInput, secondInput);
		printf("%s + %s = %s\n", firstInput, secondInput, result);
	} else if('-' == operator) {
		result = subtractSecondFromFirst(firstInput, secondInput);
		printf("%s - %s = %s\n", firstInput, secondInput, result);
	} else {
		printf("`%c` is an invalid operator! Please use either `+` or `-`\n", operator);
	}
	
	free(firstInput);
	free(secondInput);
	free(result);
	
	return 0;
}
