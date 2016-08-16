#include "calculator.h"

void add(char *romanResult, const char *romanInput1, const char *romanInput2) {
	convertToNumeral(romanResult, convertToInt(romanInput1) + convertToInt(romanInput2));
}

void subtractSecondFromFirst(char *romanResult, const char *romanInput1, const char *romanInput2) {
	convertToNumeral(romanResult, convertToInt(romanInput1) - convertToInt(romanInput2));
}
