#include "calculator.h"

void enterInput(RNResult *inputResult, const char *input) {
	strcpy(inputResult->roman, input);
	inputResult->arabic = convertToInt(input, inputResult->error);
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
