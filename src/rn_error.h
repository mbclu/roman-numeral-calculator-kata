#ifndef RN_ERROR_H_
#define RN_ERROR_H_

typedef enum {
	ERROR_NONE = 0, 
	ERROR_GREATER_THAN_MAX,
	ERROR_LESS_THAN_MIN,
	ERROR_INVALID_INPUT
} rn_error_t;

typedef struct roman_numeral_error_t {
	rn_error_t number;
	char *text;
} RNError;

static const RNError * const romanNumeralErrors[] = {
	&(struct roman_numeral_error_t) { ERROR_NONE, "No Error" },
	&(struct roman_numeral_error_t) { ERROR_GREATER_THAN_MAX, "Result is greater than max Roman Numeral value of MMMCMXCIX (3999)" },
	&(struct roman_numeral_error_t) { ERROR_LESS_THAN_MIN, "Result is less than min Roman Numeral value of I (1)" },
	&(struct roman_numeral_error_t) { ERROR_INVALID_INPUT, "Invalid input received" }
};

#endif //RN_ERROR_H_
