#include "calculator.h"
#include "converter.h"

char * add(const char *input1, const char *input2) {
	return convertToNumeral(convertToInt(input1) + convertToInt(input2));
}

char * subtractSecondFromFirst(const char *input1, const char *input2) {
	return convertToNumeral(convertToInt(input1) - convertToInt(input2));
}
