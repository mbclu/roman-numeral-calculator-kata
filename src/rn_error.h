#ifndef RN_ERROR_H_
#define RN_ERROR_H_

typedef struct roman_numeral_error_t {
	int number;
	char *text;
} RNError;

static RNError *romanNumeralErrors[] = {
	&(struct roman_numeral_error_t) { 0, "No Error" },
	&(struct roman_numeral_error_t) { 1, "Result is greater than max Roman Numeral value of MMMCMXCIX (3999)"}
};

#endif //RN_ERROR_H_
