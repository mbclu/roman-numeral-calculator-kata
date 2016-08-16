#include "converter.h"

void copyDigitToUpperCaseString(char *toUpperResult, const int digit) {
	char upperCaseDigit = (char) toupper(digit);
	memcpy(toUpperResult, &upperCaseDigit, 1);
}

int lookUpDigitValue(const char digit) {
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

	if (digit != 0 && result == 0) {
		raise(SIGINT);
	}

	return result;
}

int convertToInt(const char *numeral) {
	int result = 0;
	char currentDigit = '\0';
	char prevDigit = '\0';
	
	int i;
	size_t length = strlen(numeral);
	
	for (i = length - 1; i >= 0; --i) {
		currentDigit = numeral[i];
		if (i < length - 1) {
			prevDigit = numeral[i + 1];
		}
		
		int currentDigitValue = lookUpDigitValue(currentDigit);
		
		if (currentDigitValue < lookUpDigitValue(prevDigit)) {
			result -= currentDigitValue;
		} else {
			result += currentDigitValue;
		}
	}
	
	return result;
}

int appendCharAndDecrement(char *resultString, const int value, const RomanNumeralValues toAppend) {
	int resultantValue = value;
	
	if (resultantValue - toAppend.value >= 0) {
		resultString = realloc(resultString, strlen(toAppend.numeral));
		strcat(resultString, toAppend.numeral);
		resultantValue -= toAppend.value;
	}
	
	return resultantValue;
}

void convertToNumeral(char *romanResult, const int arabicValue) {
	int suspectIndex = 0;
	int valueRemaining = arabicValue;
	int previousValue = valueRemaining;
	
	while(valueRemaining > 0) {
		valueRemaining = appendCharAndDecrement(romanResult, valueRemaining, romanNumeralValues[suspectIndex]);
		if (valueRemaining != previousValue) {
			previousValue = valueRemaining;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	
	size_t resultSize = strlen(romanResult);
	romanResult = realloc(romanResult, resultSize + 1);
	romanResult[resultSize] = '\0';
}
