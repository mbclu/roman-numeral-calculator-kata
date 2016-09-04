#include "converter.h"

static void toUpper(char *toUpperResult, const char* text, const int length);
static const int lookUpDigitValue(const char *romanDigits, const int digitCount);
static const int appendCharAndDecrement(char *resultString, const int value, const RNValue toAppend);

const int convertToInt(const char *romanInput, RNError *error) {
	int result = 0;
	int parseIndex = 0;
	int shiftAmount = 2;
	
	int lengthToParse;
	for (lengthToParse = strlen(romanInput); lengthToParse > 0; lengthToParse -= shiftAmount) {
		int digitValue = 0;
		if (1 == lengthToParse) {
			shiftAmount = 1;
		} else {
			shiftAmount = 2;
		}
		digitValue = lookUpDigitValue(romanInput + parseIndex, shiftAmount);
		if (0 == digitValue) {
			shiftAmount = 1;
			digitValue = lookUpDigitValue(romanInput + parseIndex, shiftAmount);
		}
		parseIndex += shiftAmount;
		result += digitValue;
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

static const int lookUpDigitValue(const char *romanDigits, const int digitCount) {
	char upperCaseString[digitCount + 1];
	int result = 0;
	int i;

	toUpper(&upperCaseString, romanDigits, digitCount);

	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(&upperCaseString, romanNumeralValues[i].numeral)) {
			result = romanNumeralValues[i].value;
			break;
		}
	}

	return result;
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
