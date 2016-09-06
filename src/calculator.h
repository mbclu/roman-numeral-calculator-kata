#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "converter.h"

void enterInput(RNResult *inputResult, const char *input);
void add(RNResult *sumResult, const char *augend, const char *addend);
void subtract(RNResult *diffResult, const char *minuend, const char *subtrahend);

#endif //CALCULATOR_H_
