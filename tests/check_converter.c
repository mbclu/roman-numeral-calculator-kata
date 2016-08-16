#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <signal.h>

#include "check_suites.h"

#include "../src/converter.h"

char * result;

void setup_converter_tests() {
	result = calloc(MAX_ROMAN_NUMERAL_STRING_LENGTH, sizeof(char));
}

void teardown_converter_tests() {
	free(result);
}

START_TEST (i_represents_one)
{
	ck_assert_uint_eq(1, convertToInt("i"));
}
END_TEST

START_TEST (ii_represents_two)
{
	ck_assert_uint_eq(2, convertToInt("ii"));
}
END_TEST

START_TEST (v_represents_five)
{
	ck_assert_uint_eq(5, convertToInt("v"));
}
END_TEST

START_TEST (single_letters_by_themseleves_represent_core_values)
{
	ck_assert_uint_eq(1, convertToInt("i"));
	ck_assert_uint_eq(5, convertToInt("v"));
	ck_assert_uint_eq(10, convertToInt("x"));
	ck_assert_uint_eq(50, convertToInt("l"));
	ck_assert_uint_eq(100, convertToInt("c"));
	ck_assert_uint_eq(500, convertToInt("d"));
	ck_assert_uint_eq(1000, convertToInt("m"));
}
END_TEST

START_TEST (iv_represents_four)
{
	ck_assert_uint_eq(4, convertToInt("iv"));
}
END_TEST

START_TEST (xix_represents_nineteen)
{
	ck_assert_uint_eq(19, convertToInt("xix"));
}
END_TEST

START_TEST (mmmcdlvi_represents_three_thousand_four_hundred_fifty_six)
{
	ck_assert_uint_eq(3456, convertToInt("mmmcdlvi"));
}
END_TEST

START_TEST (uppercase_letters_also_represent_things)
{
	ck_assert_uint_eq(1, convertToInt("I"));
	ck_assert_uint_eq(5, convertToInt("V"));
	ck_assert_uint_eq(10, convertToInt("X"));
	ck_assert_uint_eq(50, convertToInt("L"));
	ck_assert_uint_eq(100, convertToInt("C"));
	ck_assert_uint_eq(500, convertToInt("D"));
	ck_assert_uint_eq(1000, convertToInt("M"));
}
END_TEST

START_TEST (one_is_represented_by_the_letter_I)
{
	convertToNumeral(result, 1);
	ck_assert_str_eq("I", result);
}
END_TEST

START_TEST (five_is_represented_by_the_letter_V)
{
	convertToNumeral(result, 5);
	ck_assert_str_eq("V", result);
}
END_TEST

START_TEST (four_is_represented_by_the_sequence_IV)
{
	convertToNumeral(result, 4);
	ck_assert_str_eq("IV", result);
}
END_TEST

START_TEST (two_is_represented_by_the_sequence_II)
{
	convertToNumeral(result, 2);
	ck_assert_str_eq("II", result);
}
END_TEST

START_TEST (nine_is_represented_by_the_sequence_IX)
{
	convertToNumeral(result, 9);
	ck_assert_str_eq("IX", result);
}
END_TEST

START_TEST (forty_is_represented_by_the_sequence_XL)
{
	convertToNumeral(result, 40);
	ck_assert_str_eq("XL", result);
}
END_TEST

START_TEST (ninety_is_represented_by_the_sequence_XC)
{
	convertToNumeral(result, 90);
	ck_assert_str_eq("XC", result);
}
END_TEST

START_TEST (four_hundred_is_represented_by_the_sequence_CD)
{
	convertToNumeral(result, 400);
	ck_assert_str_eq("CD", result);
}
END_TEST

START_TEST (nine_hundred_is_represented_by_the_sequence_CM)
{
	convertToNumeral(result, 900);
	ck_assert_str_eq("CM", result);
}
END_TEST

START_TEST (three_thousand_four_hundred_fifty_six_is_represented_by_the_sequence_mmmcdlvi)
{
	convertToNumeral(result, 3456);
	ck_assert_str_eq("MMMCDLVI", result);
}
END_TEST

START_TEST (mcxi_represents_one_one_one_one)
{
	ck_assert_uint_eq(1111, convertToInt("mcxi"));
}
END_TEST

START_TEST (convertToInt_works_twice_in_a_row)
{
	ck_assert_uint_eq(1111, convertToInt("mcxi"));
	ck_assert_uint_eq(1111, convertToInt("mcxi"));
}
END_TEST

START_TEST (calling_convert_to_int_with_invalid_character_results_in_signal_raised)
{
	ck_assert_uint_eq(0, convertToInt("F"));
}
END_TEST
Suite * make_converter_suite(void) {
	Suite *s;
	TCase *tc_convert_to_int;
	TCase *tc_convert_to_numeral;
	TCase *tc_convert_validations;

    s = suite_create("Converter Tests");

    tc_convert_to_int = tcase_create("Convert To Integer");
    tcase_add_test(tc_convert_to_int, i_represents_one);
    tcase_add_test(tc_convert_to_int, ii_represents_two);
    tcase_add_test(tc_convert_to_int, v_represents_five);
    tcase_add_test(tc_convert_to_int, single_letters_by_themseleves_represent_core_values);
    tcase_add_test(tc_convert_to_int, iv_represents_four);
    tcase_add_test(tc_convert_to_int, xix_represents_nineteen);
    tcase_add_test(tc_convert_to_int, mmmcdlvi_represents_three_thousand_four_hundred_fifty_six);
    tcase_add_test(tc_convert_to_int, uppercase_letters_also_represent_things);
    tcase_add_test(tc_convert_to_int, mcxi_represents_one_one_one_one);
    tcase_add_test(tc_convert_to_int, convertToInt_works_twice_in_a_row);
    
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
    
    tc_convert_validations = tcase_create("Convert Validations");
    tcase_add_test_raise_signal(tc_convert_validations, calling_convert_to_int_with_invalid_character_results_in_signal_raised, SIGINT);
    
    suite_add_tcase(s, tc_convert_to_int);
    suite_add_tcase(s, tc_convert_to_numeral);
    suite_add_tcase(s, tc_convert_validations);

    return s;
}