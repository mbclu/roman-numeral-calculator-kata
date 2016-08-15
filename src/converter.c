#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "roman_numerals.h"

int lookUpDigitValue(char digit) {
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

int convertToInt(char *numeral) {
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

int appendCharAndDecrement(char *resultString, int value, RomanNumeralValues toAppend) {
	int resultantValue = value;
	
	if (resultantValue - toAppend.value >= 0) {
		resultString = realloc(resultString, strlen(toAppend.numeral));
		strcat(resultString, toAppend.numeral);
		resultantValue -= toAppend.value;
	}
	
	return resultantValue;
}

char * convertToNumeral(int value) {
	char *result = calloc(1, sizeof(char));
	int suspectIndex = 0;
	int newValue = value;
	
	while(newValue > 0) {
		newValue = appendCharAndDecrement(result, value, romanNumeralValues[suspectIndex]);
		if (newValue != value) {
			value = newValue;
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
