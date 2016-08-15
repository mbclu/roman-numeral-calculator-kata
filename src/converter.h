#ifndef CONVERTER_H_
#define CONVERTER_H_

typedef struct roman_numeral_values_t {
	int value;
	char *numeral;
} RomanNumeralValues;

int convertToInt(char *numeral);
char * convertToNumeral(int value);

static const RomanNumeralValues romanNumeralValues[] = {
	{1000, "M" },
	{900, "CM" },
	{500, "D" },
	{400, "CD" },
	{100, "C" },
	{90, "XC" },
	{50, "L" },
	{40, "XL" },
	{10, "X" },
	{9, "IX" },
	{5, "V" },
	{4, "IV" },
	{1, "I" }
};

#endif //CONVERTER_H_
