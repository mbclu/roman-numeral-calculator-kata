#include "converter.h"

static const int INVALID_INDEX = -1;

static void toUpper(char *toUpperResult, const char* text, const int length);
static const int lookUpDigitIndex(const char *romanDigits, const int digitCount);
static const int appendCharAndDecrement(char *resultString, const int value, const RNValue toAppend);

const int convertToInt(const char *romanInput, RNError *error) {
	int result = 0;
	int parseIndex = 0;
	int shiftAmount = 2;
	int prevDigitIndex = INVALID_INDEX;

	int lengthToParse;
	for (lengthToParse = strlen(romanInput); lengthToParse > 0; lengthToParse -= shiftAmount) {
		int digitIndex = 0;
		if (1 == lengthToParse) {
			shiftAmount = 1;
		} else {
			shiftAmount = 2;
		}
		digitIndex = lookUpDigitIndex(romanInput + parseIndex, shiftAmount);
		if (INVALID_INDEX == digitIndex) {
			if (1 == shiftAmount) {
				setError(error, ERROR_INVALID_INPUT);
				return 0;
			}
			shiftAmount = 1;
			digitIndex = lookUpDigitIndex(romanInput + parseIndex, shiftAmount);
		}
		if (prevDigitIndex == digitIndex) {
			setError(error, ERROR_BAD_SEQUENCE);
			return 0;
		}
		if (prevDigitIndex > digitIndex) {
			printf("digit index: %i\tprevious: %i\n", digitIndex, prevDigitIndex);
			setError(error, ERROR_BAD_SEQUENCE);
			return 0;
		}
		
		prevDigitIndex = digitIndex;
		parseIndex += shiftAmount;
		result += romanNumeralValues[digitIndex].value;
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

static const int lookUpDigitIndex(const char *romanDigits, const int digitCount) {
	char upperCaseString[digitCount + 1];
	int i;

	toUpper(&upperCaseString, romanDigits, digitCount);

	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(&upperCaseString, romanNumeralValues[i].numeral)) {
			return i;
		}
	}

	return INVALID_INDEX;
}

static void toUpper(char *toUpperResult, const char* text, const int length) {
	int i;
	for (i = 0; i < length; i++) {
		toUpperResult[i] = (char) toupper(text[i]);
	}
	toUpperResult[length] = '\0';
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
