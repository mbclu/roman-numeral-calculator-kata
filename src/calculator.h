#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "converter.h"

void recallCurrentInput(RNResult *currentInputBuffer);
void recallResult(RNResult *resultBuffer);
const char recallOperator();

void resetCalculator();
void enterInput(const char *input);
void enterOperator(const char operator);
void compute();

void add(RNResult *sumResult, const char *augend, const char *addend);
void subtract(RNResult *diffResult, const char *minuend, const char *subtrahend);

#endif //CALCULATOR_H_
