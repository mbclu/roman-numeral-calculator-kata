#ifndef RN_ERROR_H_
#define RN_ERROR_H_

typedef enum {
	ERROR_NONE = 0, 
	ERROR_GREATER_THAN_MAX
} rn_error_t;

typedef struct roman_numeral_error_t {
	rn_error_t number;
	char *text;
} RNError;

static RNError *romanNumeralErrors[] = {
	&(struct roman_numeral_error_t) { ERROR_NONE, "No Error" },
	&(struct roman_numeral_error_t) { ERROR_GREATER_THAN_MAX, "Result is greater than max Roman Numeral value of MMMCMXCIX (3999)"}
};

#endif //RN_ERROR_H_
