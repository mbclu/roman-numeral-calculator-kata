#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "converter.h"
#include "roman_numerals.h"

char * digitToUpper(const int digit) {
	const int copyLength = 1;
	char *digitString = calloc(copyLength, sizeof(char));
	char upperCaseDigit = (char) toupper(digit);
	memcpy(digitString, &upperCaseDigit, copyLength);

	return digitString;
}

int lookUpDigitValue(const char digit) {
	char *upperCaseString = digitToUpper(digit);
	int result = 0;
	int i;
	
	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(upperCaseString, romanNumeralValues[i].numeral)) {
			result = romanNumeralValues[i].value;
			break;
		}
	}

	free(upperCaseString);
   
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

char * convertToNumeral(const int value) {
	char *result = calloc(1, sizeof(char));
	int suspectIndex = 0;
	int valueRemaining = value;
	int previousValue = valueRemaining;
	
	while(valueRemaining > 0) {
		valueRemaining = appendCharAndDecrement(result, valueRemaining, romanNumeralValues[suspectIndex]);
		if (valueRemaining != previousValue) {
			previousValue = valueRemaining;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	
	size_t resultSize = strlen(result);
	result = realloc(result, resultSize + 1);
	result[resultSize] = '\0';
	
	return result;
}
