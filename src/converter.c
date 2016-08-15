#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "roman_numerals.h"

int lookUpDigitValue(const int digit) {
	int result;
	
	switch (digit) {
		case 'i': case 'I': result = 1; break;
		case 'v': case 'V': result = 5; break;
		case 'x': case 'X': result = 10; break;
		case 'l': case 'L': result = 50; break;
		case 'c': case 'C': result = 100; break;
		case 'd': case 'D': result = 500; break;
		case 'm': case 'M': result = 1000; break;
		default: result = 0; break;
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
		
		int prevDigitValue = lookUpDigitValue(prevDigit);
		int currentDigitValue = lookUpDigitValue(currentDigit);
		
		if (currentDigitValue < prevDigitValue) {
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
