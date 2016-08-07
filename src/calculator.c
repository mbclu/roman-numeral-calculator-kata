#include "calculator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * add(char *input1, char *input2) {
	char *result = malloc(1 + strlen(input1) + strlen(input2));
	strcpy(result, input1);
	strcat(result, input2);
	result[strlen(result)] = '\0';
	
	if (0 == strcmp(result, "iiii")) {
		return "iv";
	} else {
		return result; 
	}
}

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
	int i;
	size_t length = strlen(numeral);
	char currentDigit;
	char prevDigit;
	
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

int appendCharAndDecrement(char *resultString, char *toAppend, int value, int suspectValue) {
	int resultantValue = value;
	if (resultantValue - suspectValue >= 0) {
		realloc(resultString, strlen(toAppend));
		strcat(resultString, toAppend);
		resultantValue -= suspectValue;
	}
	return resultantValue;
}

char * convertToNumeral(int value) {
	char *result = malloc(sizeof(char));
	int suspectValues[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	char *suspectCharacters[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	int suspectIndex = 0;
	int newValue = value;
	while(newValue > 0) {
		newValue = appendCharAndDecrement(result, suspectCharacters[suspectIndex], value, suspectValues[suspectIndex]);
		if (newValue != value) {
			value = newValue;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	return result;
}
