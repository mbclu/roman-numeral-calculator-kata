#include "calculator.h"

static RNResult *calculatorResult;
static RNResult *storedCalculatorInput;
static RNResult *currentCalculatorInput;
static char arithmeticOperator;

static void performComputation();

static void allocResult(RNResult **result);
static void freeResult(RNResult **result);
static void reallocResult(RNResult **result);
static void saveResult(RNResult *result, const char *romanValue);

static int isValidOperator(const char operator);

void recallCurrentInput(RNResult *resultBuffer) {
	if (currentCalculatorInput != NULL) {
		memcpy(resultBuffer, currentCalculatorInput, sizeof * resultBuffer);
	}
}

void recallStoredInput(RNResult *resultBuffer) {
	if (storedCalculatorInput != NULL) {
		memcpy(resultBuffer, storedCalculatorInput, sizeof * resultBuffer);
	}
}

void recallResult(RNResult *resultBuffer) {
	if (calculatorResult != NULL) {
		memcpy(resultBuffer, calculatorResult, sizeof * resultBuffer);
	}
}

const char recallOperator() {
	return arithmeticOperator;
}

void resetCalculator() {
	reallocResult(&currentCalculatorInput);
	reallocResult(&storedCalculatorInput);
	reallocResult(&calculatorResult);
}

void enterInput(const char *input) {
	reallocResult(&currentCalculatorInput);
	saveResult(currentCalculatorInput, input);
}

void enterOperator(const char operator) {
	reallocResult(&calculatorResult);
	reallocResult(&storedCalculatorInput);
	
	if (0 == strcmp(currentCalculatorInput->roman, "")) {
		setError(calculatorResult->error, ERROR_NO_INPUT_BEFORE_OPERATOR);
	} else {
		if (!isValidOperator(operator)) {
			setError(calculatorResult->error, ERROR_BAD_OPERATOR);
		} else {
			arithmeticOperator = operator;
		}
		saveResult(storedCalculatorInput, currentCalculatorInput->roman);
		reallocResult(&currentCalculatorInput);
	}
}

void compute() {
	reallocResult(&calculatorResult);
	
	if (0 == strcmp(storedCalculatorInput->roman, "")) {
		setError(calculatorResult->error, ERROR_NO_PREVIOUS_INPUT_BEFORE_COMPUTE);
	} else if (!isValidOperator(arithmeticOperator)) {
		setError(calculatorResult->error, ERROR_NO_OPERATOR);
	} else if (0 == strcmp(currentCalculatorInput->roman, "")) {
		setError(calculatorResult->error, ERROR_NO_INPUT_BEFORE_COMPUTE);
	} else {
		performComputation();
	}

	arithmeticOperator = 0;
	reallocResult(&currentCalculatorInput);
	reallocResult(&storedCalculatorInput);
}

static void performComputation() {
	if ('+' == arithmeticOperator) {
		add(calculatorResult, storedCalculatorInput->roman, currentCalculatorInput->roman);
	} else if ('-' == arithmeticOperator) {
		subtract(calculatorResult, storedCalculatorInput->roman, currentCalculatorInput->roman);
	}
}

static void allocResult(RNResult **result) {
	if (*result == NULL) {
		*result = malloc(sizeof **result);
		initRNResult(*result);
	}
}

static void freeResult(RNResult **result) {
	if (*result != NULL) {
		freeRNResult(*result);
		free(*result);
	}
	*result = NULL;
}

static void reallocResult(RNResult **result) {
	freeResult(result);
	allocResult(result);
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
