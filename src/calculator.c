#include "calculator.h"

static RNResult *calculatorResult;
static RNResult *currentCalculatorInput;
static char currentOperator;

static void resetResult();
static void initResult();
static void resetCurrentInput();
static void initCurrentInput();

static void saveResult(RNResult *result, const char *romanValue);
static int isValidOperator(const char operator);

void enterInput(const char *input) {
	resetCurrentInput();
	initCurrentInput();
	saveResult(currentCalculatorInput, input);
}

void enterOperator(const char operator) {
	if (currentCalculatorInput == NULL) {
		initResult();
		setError(calculatorResult->error, ERROR_NO_INPUT_BEFORE_OPERATOR);
	} else {
		resetResult();
		initResult();
		if (isValidOperator(operator)) {
			currentOperator = operator;
			saveResult(calculatorResult, currentCalculatorInput->roman);
		} else {
			setError(calculatorResult->error, ERROR_BAD_OPERATOR);
		}
	}
	resetCurrentInput();
}

void compute() {
	int previousResultArabic = 0;
	
	if (NULL == calculatorResult || !isValidOperator(currentOperator)) {
		resetResult();
		initResult();
		setError(calculatorResult->error, ERROR_NO_OPERATOR);
	} else {
		previousResultArabic = calculatorResult->arabic;
		resetResult();
		initResult();

		if (currentCalculatorInput == NULL) {
			setError(calculatorResult->error, ERROR_NO_INPUT_BEFORE_COMPUTE);
		} else {			
			if ('+' == currentOperator) {
				convertToNumeral(calculatorResult, previousResultArabic + currentCalculatorInput->arabic);
			} else {
				convertToNumeral(calculatorResult, previousResultArabic - currentCalculatorInput->arabic);
			}
		}
	}
	currentOperator = 0;
	resetCurrentInput();
}

void recallCurrentInput(RNResult *currentInputBuffer) {
	if (currentCalculatorInput != NULL) {
		memcpy(currentInputBuffer, currentCalculatorInput, sizeof * currentInputBuffer);
	}
}

void recallResult(RNResult *resultBuffer) {
	if (calculatorResult != NULL) {
		memcpy(resultBuffer, calculatorResult, sizeof * resultBuffer);
	}
}

const char recallOperator() {
	return currentOperator;
}

static void resetResult() {
	if (calculatorResult != NULL) {
		clearRNResult(calculatorResult);
		free(calculatorResult);
	}
	calculatorResult = NULL;
}

static void initResult() {
	calculatorResult = malloc(sizeof * calculatorResult);
	initRNResult(calculatorResult);
}

static void resetCurrentInput() {
	if (currentCalculatorInput != NULL) {
		clearRNResult(currentCalculatorInput);
		free(currentCalculatorInput);
	}
	currentCalculatorInput = NULL;
}

static void initCurrentInput() {
	currentCalculatorInput = malloc(sizeof * currentCalculatorInput);
	initRNResult(currentCalculatorInput);
}

static void saveResult(RNResult *result, const char *romanValue) {
	strcpy(result->roman, romanValue);
	result->arabic = convertToInt(romanValue, result->error);
}

static int isValidOperator(const char operator) {
	return ('+' == operator || '-' == operator);
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
