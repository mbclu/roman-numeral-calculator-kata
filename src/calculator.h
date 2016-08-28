#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "converter.h"

void add(RNResult *sum, const char *augend, const char *addend);
void subtract(RNResult *difference, const char *minuend, const char *subtrahend);

#endif //CALCULATOR_H_
