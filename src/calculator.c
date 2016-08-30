#include "calculator.h"

void add(RNResult *sum, const char *augend, const char *addend) {
	int arabicSum = convertToInt(augend, sum->error) + convertToInt(addend, sum->error);
	if (arabicSum > MAX_ROMAN_VALUE) {
		setError(sum->error, ERROR_GREATER_THAN_MAX);
		return;
	}
	convertToNumeral(sum, arabicSum);
}

void subtract(RNResult *difference, const char *minuend, const char *subtrahend) {
	int arabicDifference = convertToInt(minuend, difference->error) - convertToInt(subtrahend, difference->error);
	if (arabicDifference < MIN_ROMAN_VALUE) {
		setError(difference->error, ERROR_LESS_THAN_MIN);
		return;
	}
	convertToNumeral(difference, arabicDifference);
}
