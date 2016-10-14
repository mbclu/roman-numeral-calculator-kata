#include "converter.h"

static const int INVALID_INDEX = -1;

static void toUpper(char *toUpperResult, const char* text);
static const int lookUpDigitIndex(const char *romanDigits, const int digitCount);
static const int appendCharAndDecrement(char *resultString, const int value, const RNValue toAppend);

const int convertToInt(const char *romanInput, RNError *error) {
	char *upperCaseInput = malloc(strlen(romanInput) + 1);
	int result = 0;
	int prevDigitIndex = INVALID_INDEX;
	int totalLength = strlen(romanInput);
	int lengthToParse = totalLength;
	
	toUpper(upperCaseInput, romanInput);
	
	while (lengthToParse > 0) {
		const char *parseMarker = upperCaseInput + totalLength - lengthToParse;
		int digitIndex = 0;
		int shiftAmount = 0;

		if (1 == lengthToParse) {
			shiftAmount = 1;
		} else {
			shiftAmount = 2;
		}
		
		digitIndex = lookUpDigitIndex(parseMarker, shiftAmount);
		if (INVALID_INDEX == digitIndex) {
			digitIndex = lookUpDigitIndex(parseMarker, --shiftAmount);
		}
		
		if (0 == shiftAmount) {
			setError(error, ERROR_INVALID_INPUT);
			result = 0;
			break;
		}
		
		if (INVALID_INDEX != digitIndex && prevDigitIndex >= digitIndex) {
			setError(error, ERROR_BAD_SEQUENCE);
			result = 0;
			break;
		}
		
		prevDigitIndex = digitIndex;
		lengthToParse -= shiftAmount;
		result += romanNumeralValues[digitIndex].value;
	}
	
	free(upperCaseInput);
	return result;
}

void convertToNumeral(RNResult *result, const int arabicValue) {
	int suspectIndex = 0;
	int valueRemaining = arabicValue;
	int previousValue = valueRemaining;
	
	while(valueRemaining > 0) {
		valueRemaining = appendCharAndDecrement(result->roman, valueRemaining, romanNumeralValues[suspectIndex]);
		if (valueRemaining != previousValue) {
			previousValue = valueRemaining;
			suspectIndex = 0;
		} else {
			++suspectIndex;
		}
	}
	
	size_t resultSize = strlen(result->roman);
	result->roman = realloc(result->roman, resultSize + 1);
	result->roman[resultSize] = '\0';
}

static const int lookUpDigitIndex(const char *romanDigits, const int digitCount) {
	int resultIndex = INVALID_INDEX;
	char substring[digitCount + 1];
	strncpy(substring, romanDigits, digitCount);
	substring[digitCount] = '\0';
	int i;
	for (i = 0; i < NUM_ROMAN_LOOKUP_VALUES; i++) {
		if (0 == strcmp(substring, romanNumeralValues[i].numeral)) {
			resultIndex = i;
			break;
		}
	}

	return resultIndex;
}

static void toUpper(char *toUpperResult, const char* text) {
	const int length = strlen(text);

	int i = 0;
	while (i < length) {
		toUpperResult[i] = (char) toupper(text[i]);
		i++;
	}
	
	toUpperResult[i] = '\0';
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
