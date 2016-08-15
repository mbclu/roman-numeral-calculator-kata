#include <stdio.h>
#include <stdlib.h>
#include "src/calculator.h"

void printUsage() {
	printf("Usage:\n");
	printf("\t1.) enter the first Roman Numeral and press return\n");
	printf("\t2.) enter an operation (either `+` or `-`) and press return\n");
	printf("\t3.) enter a second Roman Numeral and press return\n");
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
