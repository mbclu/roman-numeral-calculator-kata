#include "calculator.h"

void add(char *sum, const char *augend, const char *addend) {
	
	convertToNumeral(sum, convertToInt(augend) + convertToInt(addend));
}

void subtract(char *difference, const char *minuend, const char *subtrahend) {
	convertToNumeral(difference, convertToInt(minuend) - convertToInt(subtrahend));
}
