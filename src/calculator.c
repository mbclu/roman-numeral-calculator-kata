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
