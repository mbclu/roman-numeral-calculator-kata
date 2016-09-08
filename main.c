#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "src/calculator.h"

static void printUsage(void);

int main() {
	char *firstInput = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	char *secondInput = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	char *result = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	char operator;
	
	printUsage();
	
	scanf(" %s", firstInput);
	getchar();
	scanf(" %c", &operator);
	getchar();
	scanf(" %s", secondInput);

	if ('+' == operator) {
		add(result, firstInput, secondInput);
		printf("%s + %s = %s\n", firstInput, secondInput, result);
	} else if('-' == operator) {
		subtract(result, firstInput, secondInput);
		printf("%s - %s = %s\n", firstInput, secondInput, result);
	} else {
		printf("`%c` is an invalid operator! Please use either `+` or `-`\n", operator);
	}
	
	free(firstInput);
	free(secondInput);
	free(result);
	
	return 0;
}

static void printUsage(void) {
	printf("Usage:\n");
	printf("\t1.) enter the first Roman Numeral and press return\n");
	printf("\t2.) enter an operation (either `+` or `-`) and press return\n");
	printf("\t3.) enter a second Roman Numeral and press return\n");
}
