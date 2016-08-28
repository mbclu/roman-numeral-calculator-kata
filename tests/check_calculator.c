#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "check_suites.h"

#include "../src/calculator.h"

RNResult * result;

void setup_calculator_tests() {
	result = malloc(sizeof *result);
	initRNResult(result);
}

void teardown_calculator_tests() {
	clearRNResult(result);
	free(result);
}

START_TEST (one_plus_one_is_two)
{
	add(result, "i", "i");
	ck_assert_str_eq("II", result->value);
}
END_TEST

START_TEST (one_plus_two_is_three)
{
	add(result, "i", "ii");
	ck_assert_str_eq("III", result->value);
}
END_TEST

START_TEST (two_plus_two_is_four)
{
	add(result, "ii", "ii");
	ck_assert_str_eq("IV", result->value);
}
END_TEST

START_TEST (add_returns_concatenated_result_in_correct_logical_order)
{
	add(result, "XIV", "LX");
	ck_assert_str_eq("LXXIV", result->value);
}
END_TEST

START_TEST (ii_minus_i_is_i)
{
	subtract(result, "ii", "i");
	ck_assert_str_eq("I", result->value);
}
END_TEST

START_TEST (XVII_minus_IX_is_VII)
{
	subtract(result, "XVII", "IX");
	ck_assert_str_eq("VIII", result->value);
}
END_TEST

START_TEST (MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII)
{
	subtract(result, "MMMCMXCIX", "MCXI");
	ck_assert_str_eq("MMDCCCLXXXVIII", result->value);
}
END_TEST

START_TEST (addition_with_a_result_greater_than_3999_results_in_error_return)
{
	add(result, "MMMCMXCIX", "I");
	ck_assert_int_eq(ERROR_GREATER_THAN_MAX, result->error->number);
	ck_assert_str_eq("Result is greater than max Roman Numeral value of MMMCMXCIX (3999)" , result->error->text);
}
END_TEST

Suite * make_calculator_suite(void) {
	Suite *s;
	TCase *tc_addition;
	TCase *tc_subtraction;
	TCase *tc_validation;

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
    
    tc_validation = tcase_create("Validate Results");
    tcase_add_checked_fixture(tc_validation, setup_calculator_tests, teardown_calculator_tests);
	tcase_add_test(tc_validation, addition_with_a_result_greater_than_3999_results_in_error_return);
    
    suite_add_tcase(s, tc_addition);
    suite_add_tcase(s, tc_subtraction);
    suite_add_tcase(s, tc_validation);

    return s;
}
