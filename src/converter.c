#include "converter.h"

static void copyDigitToUpperCaseString(char *toUpperResult, const int digit);
static const int lookUpDigitValue(const char digit);
static const int appendCharAndDecrement(char *resultString, const int value, const RNValues toAppend);

const int convertToInt(const char *romanNumeral) {
	int result = 0;
	char currentDigit = '\0';
	char prevDigit = '\0';
	
	int i;
	size_t length = strlen(romanNumeral);
	
	for (i = length - 1; i >= 0; --i) {
		currentDigit = romanNumeral[i];
		int currentDigitValue = lookUpDigitValue(currentDigit);
		
		int prevDigitValue = 0;
		if (i < length - 1) {
			prevDigit = romanNumeral[i + 1];
			prevDigitValue = lookUpDigitValue(prevDigit);
		}
		
		if (currentDigitValue < prevDigitValue) {
			result -= currentDigitValue;
		} else {
			result += currentDigitValue;
		}
	}
	
	return result;
}

void convertToNumeral(RNResult *romanResult, const int arabicValue) {
	int suspectIndex = 0;
	int valueRemaining = arabicValue;
	int previousValue = valueRemaining;
	
	//removes warning for now
	romanResult->error = romanNumeralErrors[0];
	
	while(valueRemaining > 0) {
		valueRemaining = appendCharAndDecrement(romanResult->value, valueRemaining, romanNumeralValues[suspectIndex]);
		if (valueRemaining != previousValue) {
			previousValue = valueRemaining;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	
	size_t resultSize = strlen(romanResult->value);
	romanResult->value = realloc(romanResult->value, resultSize + 1);
	romanResult->value[resultSize] = '\0';
}

static const int lookUpDigitValue(const char digit) {
	char upperCaseString;
	int result = 0;
	int i;

	copyDigitToUpperCaseString(&upperCaseString, digit);

	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(&upperCaseString, romanNumeralValues[i].numeral)) {
			result = romanNumeralValues[i].value;
			break;
		}
	}

	if (result == 0) {
		raise(SIGINT);
	}

	return result;
}

static void copyDigitToUpperCaseString(char *toUpperResult, const int digit) {
	char upperCaseDigit = (char) toupper(digit);
	memcpy(toUpperResult, &upperCaseDigit, 1);
}

static const int appendCharAndDecrement(char *resultString, const int value, const RNValues toAppend) {
	int resultantValue = value;
	
	if (resultantValue - toAppend.value >= 0) {
		resultString = realloc(resultString, strlen(toAppend.numeral));
		strcat(resultString, toAppend.numeral);
		resultantValue -= toAppend.value;
	}
	
	return resultantValue;
}
