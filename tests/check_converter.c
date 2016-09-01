#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <signal.h>

#include "check_suites.h"

#include "../src/converter.h"

RNResult * result;

void setup_converter_tests() {
	result = malloc(sizeof *result);
	initRNResult(result);
}

void teardown_converter_tests() {
	clearRNResult(result);
	free(result);
}

START_TEST (single_letters_by_themseleves_represent_core_values)
{
	ck_assert_uint_eq(1, convertToInt("i", result->error));
	ck_assert_uint_eq(5, convertToInt("v", result->error));
	ck_assert_uint_eq(10, convertToInt("x", result->error));
	ck_assert_uint_eq(50, convertToInt("l", result->error));
	ck_assert_uint_eq(100, convertToInt("c", result->error));
	ck_assert_uint_eq(500, convertToInt("d", result->error));
	ck_assert_uint_eq(1000, convertToInt("m", result->error));
}
END_TEST

START_TEST (uppercase_letters_also_represent_things)
{
	ck_assert_uint_eq(1, convertToInt("I", result->error));
	ck_assert_uint_eq(5, convertToInt("V", result->error));
	ck_assert_uint_eq(10, convertToInt("X", result->error));
	ck_assert_uint_eq(50, convertToInt("L", result->error));
	ck_assert_uint_eq(100, convertToInt("C", result->error));
	ck_assert_uint_eq(500, convertToInt("D", result->error));
	ck_assert_uint_eq(1000, convertToInt("M", result->error));
}
END_TEST

START_TEST (invalid_data_such_as_f_results_in_error)
{
	ck_assert_uint_eq(0, convertToInt("f", result->error));
	ck_assert_uint_eq(ERROR_INVALID_INPUT, result->error->number);
	ck_assert_str_eq("Invalid input received", result->error->text);
}
END_TEST

START_TEST (ii_represents_two)
{
	ck_assert_uint_eq(2, convertToInt("ii", result->error));
}
END_TEST

START_TEST (invalid_data_anywhere_in_the_input_results_in_error)
{
	ck_assert_uint_eq(0, convertToInt("if", result->error));
	ck_assert_uint_eq(ERROR_INVALID_INPUT, result->error->number);
	ck_assert_str_eq("Invalid input received", result->error->text);
}
END_TEST

START_TEST (iv_represents_four)
{
	ck_assert_uint_eq(4, convertToInt("iv", result->error));
}
END_TEST

START_TEST (xix_represents_nineteen)
{
	ck_assert_uint_eq(19, convertToInt("xix", result->error));
}
END_TEST

START_TEST (mmmcdlvi_represents_three_thousand_four_hundred_fifty_six)
{
	ck_assert_uint_eq(3456, convertToInt("mmmcdlvi", result->error));
}
END_TEST

START_TEST (mcxi_represents_one_one_one_one)
{
	ck_assert_uint_eq(1111, convertToInt("mcxi", result->error));
}
END_TEST

START_TEST (convertToInt_works_twice_in_a_row)
{
	ck_assert_uint_eq(1111, convertToInt("mcxi", result->error));
	ck_assert_uint_eq(1111, convertToInt("mcxi", result->error));
}
END_TEST

START_TEST (input_with_more_than_one_greater_numerals_results_in_error)
{
	ck_assert_uint_eq(0, convertToInt("DD", result->error));
	ck_assert_uint_eq(ERROR_BAD_SEQUENCE, result->error->number);
	ck_assert_str_eq("Out of sequence input received", result->error->text);
}
END_TEST

START_TEST (input_with_more_than_three_lesser_numerals_results_in_error)
{
	ck_assert_uint_eq(0, convertToInt("IIII", result->error));
	ck_assert_uint_eq(ERROR_BAD_SEQUENCE, result->error->number);
	ck_assert_str_eq("Out of sequence input received", result->error->text);
}
END_TEST

START_TEST (one_is_represented_by_the_letter_I)
{
	convertToNumeral(result, 1);
	ck_assert_str_eq("I", result->value);
}
END_TEST

START_TEST (five_is_represented_by_the_letter_V)
{
	convertToNumeral(result, 5);
	ck_assert_str_eq("V", result->value);
}
END_TEST

START_TEST (four_is_represented_by_the_sequence_IV)
{
	convertToNumeral(result, 4);
	ck_assert_str_eq("IV", result->value);
}
END_TEST

START_TEST (two_is_represented_by_the_sequence_II)
{
	convertToNumeral(result, 2);
	ck_assert_str_eq("II", result->value);
}
END_TEST

START_TEST (nine_is_represented_by_the_sequence_IX)
{
	convertToNumeral(result, 9);
	ck_assert_str_eq("IX", result->value);
}
END_TEST

START_TEST (forty_is_represented_by_the_sequence_XL)
{
	convertToNumeral(result, 40);
	ck_assert_str_eq("XL", result->value);
}
END_TEST

START_TEST (ninety_is_represented_by_the_sequence_XC)
{
	convertToNumeral(result, 90);
	ck_assert_str_eq("XC", result->value);
}
END_TEST

START_TEST (four_hundred_is_represented_by_the_sequence_CD)
{
	convertToNumeral(result, 400);
	ck_assert_str_eq("CD", result->value);
}
END_TEST

START_TEST (nine_hundred_is_represented_by_the_sequence_CM)
{
	convertToNumeral(result, 900);
	ck_assert_str_eq("CM", result->value);
}
END_TEST

START_TEST (three_thousand_four_hundred_fifty_six_is_represented_by_the_sequence_mmmcdlvi)
{
	convertToNumeral(result, 3456);
	ck_assert_str_eq("MMMCDLVI", result->value);
}
END_TEST

Suite * make_converter_suite(void) {
	Suite *s;
	TCase *tc_convert_to_int;
	TCase *tc_convert_to_numeral;
	TCase *tc_convert_validations;

    s = suite_create("Converter Tests");

    tc_convert_to_int = tcase_create("Convert To Integer");
	tcase_add_checked_fixture(tc_convert_to_int, setup_converter_tests, teardown_converter_tests);
    tcase_add_test(tc_convert_to_int, single_letters_by_themseleves_represent_core_values);
    tcase_add_test(tc_convert_to_int, uppercase_letters_also_represent_things);
    tcase_add_test(tc_convert_to_int, ii_represents_two);
    tcase_add_test(tc_convert_to_int, iv_represents_four);
    tcase_add_test(tc_convert_to_int, xix_represents_nineteen);
    tcase_add_test(tc_convert_to_int, mmmcdlvi_represents_three_thousand_four_hundred_fifty_six);
    tcase_add_test(tc_convert_to_int, mcxi_represents_one_one_one_one);
    tcase_add_test(tc_convert_to_int, convertToInt_works_twice_in_a_row);
      
    tc_convert_validations = tcase_create("Convert Validations");
    tcase_add_checked_fixture(tc_convert_validations, setup_converter_tests, teardown_converter_tests);
    tcase_add_test(tc_convert_validations, invalid_data_such_as_f_results_in_error);
    tcase_add_test(tc_convert_validations, invalid_data_anywhere_in_the_input_results_in_error);
    tcase_add_test(tc_convert_validations, input_with_more_than_one_greater_numerals_results_in_error);
    tcase_add_test(tc_convert_validations, input_with_more_than_three_lesser_numerals_results_in_error);
      
    tc_convert_to_numeral = tcase_create("Convert To Numeral");
    tcase_add_checked_fixture(tc_convert_to_numeral, setup_converter_tests, teardown_converter_tests);
    tcase_add_test(tc_convert_to_numeral, one_is_represented_by_the_letter_I);
    tcase_add_test(tc_convert_to_numeral, five_is_represented_by_the_letter_V);
    tcase_add_test(tc_convert_to_numeral, two_is_represented_by_the_sequence_II);
    tcase_add_test(tc_convert_to_numeral, four_is_represented_by_the_sequence_IV);
    tcase_add_test(tc_convert_to_numeral, nine_is_represented_by_the_sequence_IX);
    tcase_add_test(tc_convert_to_numeral, forty_is_represented_by_the_sequence_XL);
    tcase_add_test(tc_convert_to_numeral, ninety_is_represented_by_the_sequence_XC);
    tcase_add_test(tc_convert_to_numeral, four_hundred_is_represented_by_the_sequence_CD);
    tcase_add_test(tc_convert_to_numeral, nine_hundred_is_represented_by_the_sequence_CM);
    tcase_add_test(tc_convert_to_numeral, three_thousand_four_hundred_fifty_six_is_represented_by_the_sequence_mmmcdlvi);

    suite_add_tcase(s, tc_convert_to_int);
    suite_add_tcase(s, tc_convert_to_numeral);    
    suite_add_tcase(s, tc_convert_validations);

    return s;
}
