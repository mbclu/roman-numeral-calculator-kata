#ifndef ROMAN_NUMERALS_H_
#define ROMAN_NUMERALS_H_

static const int NUM_ROMAN_LOOKUP_VALUES = 13;

typedef struct roman_numeral_values_t {
	int value;
	char *numeral;
} RNValues;

static const RNValues romanNumeralValues[] = {
	{ 1000, "M"  },
	{ 900,  "CM" },
	{ 500,  "D"  },
	{ 400,  "CD" },
	{ 100,  "C"  },
	{ 90,   "XC" },
	{ 50,   "L"  },
	{ 40,   "XL" },
	{ 10,   "X"  },
	{ 9,    "IX" },
	{ 5,    "V"  },
	{ 4,    "IV" },
	{ 1,    "I"  }
};

#endif //ROMAN_NUMERALS_H_
