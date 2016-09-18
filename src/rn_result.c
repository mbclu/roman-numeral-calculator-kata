#include <string.h>

#include "rn_result.h"

void initRNResult(RNResult *result) {
	result->roman = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
	result->error = malloc(sizeof result->error);
	setError(result->error, ERROR_NONE);
	result->arabic = 0;
}

void clearRNResult(RNResult *result) {
	free(result->roman);
	result->roman = NULL;
	free(result->error);
	result->error = NULL;
	result->arabic = 0;
}

void setError(RNError *error, const rn_error_t errorType) {
	memcpy(error, romanNumeralErrors[errorType], sizeof *error);
}
