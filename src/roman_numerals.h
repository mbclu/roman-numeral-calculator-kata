#ifndef ROMAN_NUMERALS_H_
#define ROMAN_NUMERALS_H_

static const int NUM_ROMAN_LOOKUP_VALUES = 17;
static const int MAX_ROMAN_VALUE = 3999;
static const int MIN_ROMAN_VALUE = 1;
static const int GREATER_NUMERAL_REPEAT_LIMIT = 1;
static const int LESSER_NUMERAL_REPEAT_LIMIT = 3;

typedef struct roman_numeral_values_t {
	int value;
	char *numeral;
} RNValue;

static const RNValue romanNumeralValues[] = {
	{ 2000, "MM" },
	{ 1000, "M"  },
	{ 900,  "CM" },
	{ 500,  "D"  },
	{ 400,  "CD" },
	{ 200,  "CC" },
	{ 100,  "C"  },
	{ 90,   "XC" },
	{ 50,   "L"  },
	{ 40,   "XL" },
	{ 20,   "XX" },
	{ 10,   "X"  },
	{ 9,    "IX" },
	{ 5,    "V"  },
	{ 4,    "IV" },
	{ 2,    "II" },
	{ 1,    "I"  }
};

#endif //ROMAN_NUMERALS_H_
