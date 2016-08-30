#include <string.h>

#include "rn_result.h"

void initRNResult(RNResult *result) {
	result->error = malloc(sizeof result->error);
	setError(result->error, ERROR_NONE);
	result->value = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
}

void clearRNResult(RNResult *result) {
	free(result->value);
	result->value = NULL;
	result->error = NULL;
}

void setError(RNError *error, const rn_error_t errorType) {
	memcpy(error, romanNumeralErrors[errorType], sizeof *error);
}
