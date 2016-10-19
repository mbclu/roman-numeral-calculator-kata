#include <stdio.h>
#include <stdlib.h>
#include "src/calculator.h"

static char* input;
static RNResult *result;

static void printUsage(void);
static int attemptInput(void);
static int attemptOperator(void);
static int printResult(void);
static int checkForErrors(void);

int main() {
	int error = ERROR_NONE;
	printUsage();
	
	result = malloc(sizeof *result);
	initRNResult(result);
	resetCalculator();
	
	error = attemptInput();
	if (ERROR_NONE != error) { return error; }
	error = attemptOperator(); 
	if (ERROR_NONE != error) { return error; }
	error = attemptInput();
	if (ERROR_NONE != error) { return error; }

	compute();
	
	error = printResult();
	if (ERROR_NONE != error) { return error; }
	
	return 0;
}

static void printUsage(void) {
	printf("------------------------------------------------------------------\n");
	printf("Usage:\n");
	printf("------------------------------------------------------------------\n");
	printf("1.) enter the first Roman Numeral and press return\n");
	printf("2.) enter an operation (either `+` or `-`) and press return\n");
	printf("3.) enter a second Roman Numeral and press return\n");
	printf("------------------------------------------------------------------\n");
}

static int attemptInput(void) {
	input = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	scanf(" %s", input);
	getchar();
	enterInput(input);
	free(input);
	return checkForErrors();
}

static int attemptOperator(void) {
	char operator;
	scanf(" %c", &operator);
	getchar();
	enterOperator(operator);
	return checkForErrors();
}

static int printResult(void) {
	recallResult(result);
	printf("-----\n");
	printf("%s\n", result->roman);
	return checkForErrors();
}

static int checkForErrors(void) {
	recallResult(result);
	if (ERROR_NONE != result->error->number) {
		printf("Sorry, but something fun happened -> %s\n", result->error->text);
		return result->error->number;
	}
	return 0;
}
