#include "rn_result.h"

void initRNResult(RNResult *result) {
	result->value = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	result->error = romanNumeralErrors[0];
}

void clearRNResult(RNResult *result) {
	free(result->value);
	result->error = NULL;
}