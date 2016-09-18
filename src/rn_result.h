#ifndef RN_RESULT_H_
#define RN_RESULT_H_

#include <stdlib.h>

#include "rn_error.h"

static const int MAX_ROMAN_NUMERAL_STRING_LENGTH = 16;

typedef struct roman_numeral_math_result_t {
	int arabic;
	char *roman;
	RNError *error;
} RNResult;

void initRNResult(RNResult *result);
void freeRNResult(RNResult *result);
void setError(RNError *error, const rn_error_t errorType);

#endif //RN_RESULT_H_
