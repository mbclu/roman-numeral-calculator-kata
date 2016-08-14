#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "check_suites.h"

#include "../src/calculator.h"

char * result;

void setup_calculator_tests() {
}

void teardown_calculator_tests() {
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

START_TEST (MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII)
{
	result = subtractSecondFromFirst("MMMCMXCIX", "MCXI");
	ck_assert_str_eq("MMDCCCLXXXVIII", result);
}
END_TEST

Suite * make_calculator_suite(void) {
	Suite *s;
	TCase *tc_addition;
	TCase *tc_subtraction;

    s = suite_create("Calculator Tests");

    tc_addition = tcase_create("Addition");
    tcase_add_checked_fixture(tc_addition, setup_calculator_tests, teardown_calculator_tests);
    tcase_add_test(tc_addition, one_plus_one_is_two);
    tcase_add_test(tc_addition, one_plus_two_is_three);
    tcase_add_test(tc_addition, two_plus_two_is_four);
    tcase_add_test(tc_addition, add_returns_concatenated_result_in_correct_logical_order);
        
    tc_subtraction = tcase_create("Subtraction");
	tcase_add_checked_fixture(tc_subtraction, setup_calculator_tests, teardown_calculator_tests);
    tcase_add_test(tc_subtraction, ii_minus_i_is_i);
    tcase_add_test(tc_subtraction, XVII_minus_IX_is_VII);
    tcase_add_test(tc_subtraction, MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII);
    
    suite_add_tcase(s, tc_addition);
    suite_add_tcase(s, tc_addition);

    return s;
}
