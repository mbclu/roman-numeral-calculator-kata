#include "calculator.h"

static RNResult *calculatorResult;
static RNResult *currentCalculatorInput;
static char currentOperator;

static void reset(RNResult **result);
static void resetResult();
static void resetCurrentInput();

static void init(RNResult **result);

static void saveResult(RNResult *result, const char *romanValue);
static int isValidOperator(const char operator);

void enterInput(const char *input) {
	resetCurrentInput();
	saveResult(currentCalculatorInput, input);
}

void enterOperator(const char operator) {
	if (currentCalculatorInput == NULL) {
		resetResult();
		setError(calculatorResult->error, ERROR_NO_INPUT_BEFORE_OPERATOR);
	} else {
		resetResult();
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
		setError(calculatorResult->error, ERROR_NO_OPERATOR);
	} else {
		previousResultArabic = calculatorResult->arabic;
		resetResult();

		if (0 == currentCalculatorInput->arabic) {
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

static void init(RNResult **result) {
	if (*result == NULL) {
		*result = malloc(sizeof **result);
		initRNResult(*result);
	}
}

static void reset(RNResult **result) {
	if (*result != NULL) {
		clearRNResult(*result);
		free(*result);
	}
	*result = NULL;
}

static void resetResult() {
	reset(&calculatorResult);
	init(&calculatorResult);
}

static void resetCurrentInput() {
	reset(&currentCalculatorInput);
	init(&currentCalculatorInput);
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
