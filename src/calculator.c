#include "calculator.h"

void add(RNResult *sum, const char *augend, const char *addend) {
	int arabicSum = convertToInt(augend) + convertToInt(addend);
	if (arabicSum > MAX_ROMAN_VALUE) {
		clearRNResult(sum);
		sum->error = romanNumeralErrors[ERROR_GREATER_THAN_MAX];
		return;
	}
	convertToNumeral(sum, arabicSum);
}

void subtract(RNResult *difference, const char *minuend, const char *subtrahend) {
	convertToNumeral(difference, convertToInt(minuend) - convertToInt(subtrahend));
}
