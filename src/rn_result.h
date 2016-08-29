#ifndef RN_RESULT_H_
#define RN_RESULT_H_

#include <stdlib.h>

#include "rn_error.h"

static const int MAX_ROMAN_NUMERAL_STRING_LENGTH = 16;

typedef struct roman_numeral_math_result_t {
	char *value;
	RNError *error;
} RNResult;

void initRNResult(RNResult *result);
void clearRNResult(RNResult *result);
void setError(RNResult *result, const rn_error_t errorType);

#endif //RN_RESULT_H_
