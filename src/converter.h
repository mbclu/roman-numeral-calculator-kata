#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "constants.h"
#include "roman_numerals.h"

const int convertToInt(const char *romanNumeral);
void convertToNumeral(char *romanResult, const int arabicValue);

#endif //CONVERTER_H_
