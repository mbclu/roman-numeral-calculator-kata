#include "converter.h"

static void copyDigitToUpperCaseString(char *toUpperResult, const int digit);
static const int lookUpDigitValue(const char romanDigit);
static const int appendCharAndDecrement(char *resultString, const int value, const RNValue toAppend);
static const int isGreaterDigit(const char romanDigit);

const int convertToInt(const char *romanInput, RNError *error) {
	int result = 0;
	char rightDigit = '\0';
	char leftDigit = '\0';
	int repeatDigitCount = 0;
	
	int i;
	size_t length = strlen(romanInput);
	
	for (i = length - 1; i >= 0; --i) {
		rightDigit = romanInput[i];
		int rightDigitValue = lookUpDigitValue(rightDigit);
		if (0 == rightDigitValue) {
			setError(error, ERROR_INVALID_INPUT);
			return 0;
		}
		
		int leftDigitValue = 0;
		if (i < length - 1) {
			leftDigit = romanInput[i + 1];
			leftDigitValue = lookUpDigitValue(leftDigit);
		}
		
		if (rightDigitValue < leftDigitValue) {
			result -= rightDigitValue;
		} else {
			if (rightDigit == leftDigit) {
				repeatDigitCount++;
				if (repeatDigitCount > 0 && isGreaterDigit(rightDigit)) {
					setError(error, ERROR_BAD_SEQUENCE);
					return 0;
				} else if (repeatDigitCount > 2 && !isGreaterDigit(rightDigit)) {
					setError(error, ERROR_BAD_SEQUENCE);
					return 0;
				}
			} else {
				repeatDigitCount = 0;
			}
			result += rightDigitValue;
		}
	}
	
	return result;
}

void convertToNumeral(RNResult *result, const int arabicValue) {
	int suspectIndex = 0;
	int valueRemaining = arabicValue;
	int previousValue = valueRemaining;
	
	while(valueRemaining > 0) {
		valueRemaining = appendCharAndDecrement(result->value, valueRemaining, romanNumeralValues[suspectIndex]);
		if (valueRemaining != previousValue) {
			previousValue = valueRemaining;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	
	size_t resultSize = strlen(result->value);
	result->value = realloc(result->value, resultSize + 1);
	result->value[resultSize] = '\0';
}

static const int lookUpDigitValue(const char romanDigit) {
	char upperCaseString;
	int result = 0;
	int i;

	copyDigitToUpperCaseString(&upperCaseString, romanDigit);

	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(&upperCaseString, romanNumeralValues[i].numeral)) {
			result = romanNumeralValues[i].value;
			break;
		}
	}

	return result;
}

static void copyDigitToUpperCaseString(char *toUpperResult, const int digit) {
	char upperCaseDigit = (char) toupper(digit);
	memcpy(toUpperResult, &upperCaseDigit, 1);
}

static const int appendCharAndDecrement(char *resultString, const int value, const RNValue toAppend) {
	int resultantValue = value;
	
	if (resultantValue - toAppend.value >= 0) {
		resultString = realloc(resultString, strlen(toAppend.numeral));
		strcat(resultString, toAppend.numeral);
		resultantValue -= toAppend.value;
	}
	
	return resultantValue;
}

static const int isGreaterDigit(const char romanDigit) {
	char upperCaseString;
	copyDigitToUpperCaseString(&upperCaseString, romanDigit);
	switch (upperCaseString) {
		case 'V':
		case 'L': 
		case 'D':
			return 1;
	}
	return 0;
}

