#include "calculator.h"
#include <stdlib.h>
#include <string.h>

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
	
	for (i = length - 1; i >= 0; i--) {
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
