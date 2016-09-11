#ifndef RN_ERROR_H_
#define RN_ERROR_H_

typedef enum {
	ERROR_NONE = 0, 
	ERROR_GREATER_THAN_MAX,
	ERROR_LESS_THAN_MIN,
	ERROR_INVALID_INPUT,
	ERROR_BAD_SEQUENCE,
	ERROR_BAD_OPERATOR,
	ERROR_NO_INPUT_BEFORE_OPERATOR,
	ERROR_NO_OPERATOR,
	ERROR_NO_INPUT_BEFORE_COMPUTE
} rn_error_t;

typedef struct roman_numeral_error_t {
	rn_error_t number;
	char *text;
} RNError;

static const RNError * const romanNumeralErrors[] = {
	&(struct roman_numeral_error_t) { ERROR_NONE, "No Error" },
	&(struct roman_numeral_error_t) { ERROR_GREATER_THAN_MAX, "Result is greater than max Roman Numeral value of MMMCMXCIX (3999)" },
	&(struct roman_numeral_error_t) { ERROR_LESS_THAN_MIN, "Result is less than min Roman Numeral value of I (1)" },
	&(struct roman_numeral_error_t) { ERROR_INVALID_INPUT, "Invalid input received" },
	&(struct roman_numeral_error_t) { ERROR_BAD_SEQUENCE, "Out of sequence input received" },
	&(struct roman_numeral_error_t) { ERROR_BAD_OPERATOR, "Invalid operator (must be one of '+' or '-')" },
	&(struct roman_numeral_error_t) { ERROR_NO_INPUT_BEFORE_OPERATOR, "Must input roman numeral before math operator" },
	&(struct roman_numeral_error_t) { ERROR_NO_OPERATOR, "Must input operator before compute" },
	&(struct roman_numeral_error_t) { ERROR_NO_INPUT_BEFORE_COMPUTE, "Must input roman numeral before compute" }
};

#endif //RN_ERROR_H_
