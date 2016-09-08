#include "calculator.h"

static RNResult *calculatorResult;
static RNResult *currentCalculatorInput;
static char currentOperator;

static void saveResult(RNResult *result, const char *romanValue);

void enterInput(const char *input) {
	currentCalculatorInput = malloc(sizeof * currentCalculatorInput);
	initRNResult(currentCalculatorInput);
	saveResult(currentCalculatorInput, input);
}

void enterOperator(const char operator) {
	calculatorResult = malloc(sizeof * calculatorResult);
	initRNResult(calculatorResult);
	if (currentCalculatorInput != NULL && currentCalculatorInput->roman != NULL) {
		if (operator == '+' || operator == '-') {
			currentOperator = operator;
			saveResult(calculatorResult, currentCalculatorInput->roman);
		} else {
			setError(calculatorResult->error, ERROR_BAD_OPERATOR);
		}
	} else {
		if (calculatorResult != NULL && calculatorResult->error != NULL) {
			setError(calculatorResult->error, ERROR_NO_INPUT);
		}
	}
}

void recallCurrentInput(RNResult *currentInputBuffer) {
	memcpy(currentInputBuffer, currentCalculatorInput, sizeof * currentInputBuffer);
}

void recallResult(RNResult *resultBuffer) {
	memcpy(resultBuffer, calculatorResult, sizeof * resultBuffer);
}

const char recallOperator() {
	return currentOperator;
}

void clearResult() {
	if (calculatorResult != NULL) {
		clearRNResult(calculatorResult);
		free(calculatorResult);
		calculatorResult = NULL;
	}
}

void clearCurrentInput() {
	if (currentCalculatorInput != NULL) {
		clearRNResult(currentCalculatorInput);
		free(currentCalculatorInput);
		currentCalculatorInput = NULL;
	}
}

static void saveResult(RNResult *result, const char *romanValue) {
	//result = malloc(sizeof * result);
	//initRNResult(result);
	strcpy(result->roman, romanValue);
	result->arabic = convertToInt(romanValue, result->error);
}

void add(RNResult *sumResult, const char *augend, const char *addend) {
	int arabicSum = 0;
	int augendValue = convertToInt(augend, sumResult->error);
	if (ERROR_NONE == sumResult->error->number) {
		int addendValue = convertToInt(addend, sumResult->error);
		if (ERROR_NONE == sumResult->error->number) {
			arabicSum = augendValue + addendValue;
			if (arabicSum > MAX_ROMAN_VALUE) {
				setError(sumResult->error, ERROR_GREATER_THAN_MAX);
				return;
			}
			convertToNumeral(sumResult, arabicSum);
		}
	}
}

void subtract(RNResult *diffResult, const char *minuend, const char *subtrahend) {
	int arabicDifference = 0;
	int minuendValue = convertToInt(minuend, diffResult->error);
	if (ERROR_NONE == diffResult->error->number) {
		int subtrahendValue = convertToInt(subtrahend, diffResult->error);
		if (ERROR_NONE == diffResult->error->number) {
			arabicDifference = minuendValue - subtrahendValue;
			if (arabicDifference < MIN_ROMAN_VALUE) {
				setError(diffResult->error, ERROR_LESS_THAN_MIN);
				return;
			}
			convertToNumeral(diffResult, arabicDifference);
		}
	}
}
