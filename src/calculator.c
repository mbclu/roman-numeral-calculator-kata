#include "calculator.h"

void add(RNResult *sum, const char *augend, const char *addend) {
	int arabicSum = convertToInt(augend) + convertToInt(addend);
	if (arabicSum > MAX_ROMAN_VALUE) {
		setError(sum, ERROR_GREATER_THAN_MAX);
		return;
	}
	convertToNumeral(sum, arabicSum);
}

void subtract(RNResult *difference, const char *minuend, const char *subtrahend) {
	int arabicSum = convertToInt(minuend) - convertToInt(subtrahend);
	if (arabicSum < MIN_ROMAN_VALUE) {
		setError(difference, ERROR_LESS_THAN_MIN);
		return;
	}
	convertToNumeral(difference, convertToInt(minuend) - convertToInt(subtrahend));
}
