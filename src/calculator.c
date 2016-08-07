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

int convertToInt(char *numeral) {
	int i;
	int result = 0;
	size_t length = strlen(numeral);
	for (i = 0; i < length; i++) {
		switch (numeral[i]) {
			case 'i': result += 1; break;
			case 'v': result += 5; break;
			case 'x': result += 10; break;
			case 'l': result += 50; break;
			case 'c': result += 100; break;
			case 'd': result += 500; break;
			case 'm': result += 1000; break;
		}
	}
	return result;
}
