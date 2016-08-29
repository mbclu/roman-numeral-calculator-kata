#include "rn_result.h"

void initRNResult(RNResult *result) {
	setError(result, ERROR_NONE);
	result->value = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
}

void clearRNResult(RNResult *result) {
	free(result->value);
	result->value = NULL;
	result->error = NULL;
}

void setError(RNResult *result, const rn_error_t errorType) {
	result->error = romanNumeralErrors[errorType];
}
