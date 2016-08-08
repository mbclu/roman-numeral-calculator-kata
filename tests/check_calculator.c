#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "../src/calculator.h"

char * result;

void setup() {
}

void teardown() {
	free(result);
}

START_TEST (one_plus_one_is_two)
{
	result = add("i", "i");
	ck_assert_str_eq("II", result);
}
END_TEST

START_TEST (one_plus_two_is_three)
{
	result = add("i", "ii");
	ck_assert_str_eq("III", result);
}
END_TEST

START_TEST (two_plus_two_is_four)
{
	result = add("ii", "ii");
	ck_assert_str_eq("IV", result);
}
END_TEST

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
	result = convertToNumeral(1);
	ck_assert_str_eq("I", result);
}
END_TEST

START_TEST (five_is_represented_by_the_letter_V)
{
	result = convertToNumeral(5);
	ck_assert_str_eq("V", result);
}
END_TEST

START_TEST (four_is_represented_by_the_sequence_IV)
{
	result = convertToNumeral(4);
	ck_assert_str_eq("IV", result);
}
END_TEST

START_TEST (two_is_represented_by_the_sequence_II)
{
	result = convertToNumeral(2);
	ck_assert_str_eq("II", result);
}
END_TEST

START_TEST (nine_is_represented_by_the_sequence_IX)
{
	result = convertToNumeral(9);
	ck_assert_str_eq("IX", result);
}
END_TEST

START_TEST (forty_is_represented_by_the_sequence_XL)
{
	result = convertToNumeral(40);
	ck_assert_str_eq("XL", result);
}
END_TEST

START_TEST (ninety_is_represented_by_the_sequence_XC)
{
	result = convertToNumeral(90);
	ck_assert_str_eq("XC", result);
}
END_TEST

START_TEST (four_hundred_is_represented_by_the_sequence_CD)
{
	result = convertToNumeral(400);
	ck_assert_str_eq("CD", result);
}
END_TEST

START_TEST (nine_hundred_is_represented_by_the_sequence_CM)
{
	result = convertToNumeral(900);
	ck_assert_str_eq("CM", result);
}
END_TEST

START_TEST (three_thousand_four_hundred_fifty_six_is_represented_by_the_sequence_mmmcdlvi)
{
	result = convertToNumeral(3456);
	ck_assert_str_eq("MMMCDLVI", result);
}
END_TEST

START_TEST (add_returns_concatenated_result_in_correct_logical_order)
{
	result = add("XIV", "LX");
	ck_assert_str_eq("LXXIV", result);
}
END_TEST

START_TEST (ii_minus_i_is_i)
{
	result = subtractSecondFromFirst("ii", "i");
	ck_assert_str_eq("I", result);
}
END_TEST

START_TEST (XVII_minus_IX_is_VII)
{
	result = subtractSecondFromFirst("XVII", "IX");
	ck_assert_str_eq("VIII", result);
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

START_TEST (MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII)
{
	result = subtractSecondFromFirst("MMMCMXCIX", "MCXI");
	ck_assert_str_eq("MMDCCCLXXXVIII", result);
}
END_TEST

Suite * calculator_suite(void) {
	Suite *s;
	TCase *tc_core;
	TCase *tc_convert_to_int;
	TCase *tc_convert_to_numeral;

    s = suite_create("Calculator Tests");

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
    tcase_add_checked_fixture(tc_convert_to_numeral, setup, teardown);
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
    
    tc_core = tcase_create("Addition and Subtraction");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    
    tcase_add_test(tc_core, one_plus_one_is_two);
    tcase_add_test(tc_core, one_plus_two_is_three);
    tcase_add_test(tc_core, two_plus_two_is_four);
    tcase_add_test(tc_core, add_returns_concatenated_result_in_correct_logical_order);
    
    tcase_add_test(tc_core, ii_minus_i_is_i);
    tcase_add_test(tc_core, XVII_minus_IX_is_VII);
    tcase_add_test(tc_core, MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII);
    
    suite_add_tcase(s, tc_convert_to_int);
    suite_add_tcase(s, tc_convert_to_numeral);
    suite_add_tcase(s, tc_core);

    return s;
}
	
int main() {
	int number_failed;
    Suite *s;
    SRunner *sr;

    s = calculator_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
