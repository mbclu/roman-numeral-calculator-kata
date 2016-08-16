#include "calculator.h"

void add(char *romanSum, const char *augend, const char *addend) {
	int arabicSum = convertToInt(augend) + convertToInt(addend);
	convertToNumeral(romanSum, arabicSum);
}

void subtract(char *romanDifference, const char *minuend, const char *subtrahend) {
	int arabicDifference = convertToInt(minuend) - convertToInt(subtrahend);
	convertToNumeral(romanDifference, arabicDifference);
}
