#include "calculator.h"
#include "converter.h"

char * add(char *input1, char *input2) {
	return convertToNumeral(convertToInt(input1) + convertToInt(input2));
}

char * subtractSecondFromFirst(char *input1, char *input2) {
	return convertToNumeral(convertToInt(input1) - convertToInt(input2));
}
