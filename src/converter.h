#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "roman_numerals.h"
#include "rn_result.h"

const int convertToInt(const char *romanInput, RNError *error);
void convertToNumeral(RNResult *result, const int arabicValue);

#endif //CONVERTER_H_
