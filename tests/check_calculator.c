#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "check_suites.h"

#include "../src/calculator.h"

RNResult * result;

void setup_calculator_tests() {
	resetCalculator();
	result = malloc(sizeof *result);
	initRNResult(result);
}

void teardown_calculator_tests() {
	freeRNResult(result);
	free(result);
	result = NULL;
}

START_TEST (one_plus_one_is_two)
{
	add(result, "i", "i");
	ck_assert_str_eq("II", result->roman);
}
END_TEST

START_TEST (one_plus_two_is_three)
{
	add(result, "i", "ii");
	ck_assert_str_eq("III", result->roman);
}
END_TEST

START_TEST (two_plus_two_is_four)
{
	add(result, "ii", "ii");
	ck_assert_str_eq("IV", result->roman);
}
END_TEST

START_TEST (add_returns_concatenated_result_in_correct_logical_order)
{
	add(result, "XIV", "LX");
	ck_assert_str_eq("LXXIV", result->roman);
}
END_TEST

START_TEST (ii_minus_i_is_i)
{
	subtract(result, "ii", "i");
	ck_assert_str_eq("I", result->roman);
}
END_TEST

START_TEST (XVII_minus_IX_is_VII)
{
	subtract(result, "XVII", "IX");
	ck_assert_str_eq("VIII", result->roman);
}
END_TEST

START_TEST (MMMCMXCIX_minus_MCXI_is_MMDCCCLXXXVIII)
{
	subtract(result, "MMMCMXCIX", "MCXI");
	ck_assert_str_eq("MMDCCCLXXXVIII", result->roman);
}
END_TEST

START_TEST (addition_with_a_result_greater_than_3999_results_in_error)
{
	add(result, "MMMCMXCIX", "I");
	ck_assert_uint_eq(ERROR_GREATER_THAN_MAX, result->error->number);
	ck_assert_str_eq("Result is greater than max Roman Numeral value of MMMCMXCIX (3999)", result->error->text);
}
END_TEST

START_TEST (addition_with_a_result_greater_than_3999_results_in_an_empty_result_value)
{
	add(result, "MMMCMXCIX", "I");
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (subtraction_with_a_result_equal_to_zero_results_in_error)
{
	subtract(result, "I", "I");
	ck_assert_uint_eq(ERROR_LESS_THAN_MIN, result->error->number);
	ck_assert_str_eq("Result is less than min Roman Numeral value of I (1)", result->error->text);
}
END_TEST

START_TEST (subtraction_with_a_result_equal_to_zero_results_in_an_empty_result_value)
{
	subtract(result, "I", "I");
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (augend_which_fails_to_be_converted_to_int_should_return_empty_string_when_added)
{
	add(result, "AHHHHHHHH", "I");
	ck_assert_uint_eq(ERROR_INVALID_INPUT, result->error->number);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (addend_which_fails_to_be_converted_to_int_should_return_empty_string_when_added)
{
	add(result, "I", "IIIIIIIII");
	ck_assert_uint_eq(ERROR_BAD_SEQUENCE, result->error->number);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (minuend_which_fails_to_be_converted_to_int_should_return_empty_string_when_subtracted)
{
	subtract(result, "I", "IIIIIIIII");
	ck_assert_uint_eq(ERROR_BAD_SEQUENCE, result->error->number);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (subtrahend_which_fails_to_be_converted_to_int_should_return_empty_string_when_subtracted)
{
	subtract(result, "AHHHHHHHH", "I");
	ck_assert_uint_eq(ERROR_INVALID_INPUT, result->error->number);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (input_which_is_entered_is_stored_in_the_given_result_buffer)
{
	enterInput("i");
	recallCurrentInput(result);
	ck_assert_str_eq("i", result->roman);
	ck_assert_uint_eq(1, result->arabic);
}
END_TEST

START_TEST (when_plus_operator_is_input_the_current_calculator_input_is_stored)
{
	enterInput("vi");
	enterOperator('+');
	recallStoredInput(result);
	ck_assert_uint_eq('+', recallOperator());
	ck_assert_str_eq("vi", result->roman);
}
END_TEST

START_TEST (when_minus_operator_is_input_the_current_calculator_input_is_stored)
{
	enterInput("mx");
	enterOperator('-');
	recallStoredInput(result);
	ck_assert_uint_eq('-', recallOperator());
	ck_assert_str_eq("mx", result->roman);
}
END_TEST

START_TEST (when_non_plus_or_minus_operator_is_input_an_error_is_stored)
{
	enterInput("I");
	enterOperator('8');
	recallResult(result);	
	ck_assert_uint_eq(ERROR_BAD_OPERATOR, result->error->number);
	ck_assert_str_eq("Invalid operator (must be one of \'+\' or \'-\')", result->error->text);
}
END_TEST

START_TEST (when_operator_is_input_before_valid_roman_input_error_is_stored)
{
	enterOperator('+');
	recallResult(result);
	ck_assert_uint_eq(ERROR_NO_INPUT_BEFORE_OPERATOR, result->error->number);
	ck_assert_str_eq("Must input roman numeral before math operator", result->error->text);
}
END_TEST

START_TEST (given_the_sequence_valid_input_plus_operator_valid_input_compute_the_addition_result_is_stored_in_calculatorResult)
{
	enterInput("V");
	enterOperator('+');
	enterInput("X");
	compute();
	recallResult(result);
	ck_assert_str_eq("XV", result->roman);
}
END_TEST

START_TEST (given_the_sequence_valid_input_minus_operator_valid_input_compute_the_subtraction_result_is_stored_in_calculatorResult)
{
	enterInput("XX");
	enterOperator('-');
	enterInput("XI");
	compute();
	recallResult(result);
	ck_assert_str_eq("IX", result->roman);
}
END_TEST

START_TEST (compute_sets_no_input_error_when_previous_result_is_not_stored)
{
	enterInput("VII");
	compute();
	recallResult(result);
	ck_assert_uint_eq(ERROR_NO_PREVIOUS_INPUT_BEFORE_COMPUTE, result->error->number);
	ck_assert_str_eq("Must input roman numeral before compute", result->error->text);
}
END_TEST

START_TEST (compute_sets_no_operator_error_when_valid_operator_is_not_stored)
{
	enterInput("VII");
	enterOperator('j');
	compute();
	recallResult(result);
	ck_assert_uint_eq(ERROR_NO_OPERATOR, result->error->number);
	ck_assert_str_eq("Must input operator before compute", result->error->text);
}
END_TEST

START_TEST (compute_sets_no_current_input_error_when_nothing_is_stored_in_current_input)
{
	enterInput("MM");
	enterOperator('-');
	compute();
	recallResult(result);
	ck_assert_uint_eq(ERROR_NO_INPUT_BEFORE_COMPUTE, result->error->number);
	ck_assert_str_eq("Must input second roman numeral before compute", result->error->text);
}
END_TEST

START_TEST (operator_and_stored_input_and_current_input_are_reset_after_compute)
{
	enterInput("MM");
	enterOperator('-');
	enterInput("M");
	compute();
	recallCurrentInput(result);
	ck_assert_str_eq("", result->roman);
	recallStoredInput(result);
	ck_assert_str_eq("", result->roman);
	ck_assert_uint_eq(0, recallOperator());
}
END_TEST

START_TEST (resetCalculator_clears_out_current_input)
{
	enterInput("XVIII");
	resetCalculator();
	recallCurrentInput(result);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (resetCalculator_clears_out_stored_input)
{
	enterInput("XVIII");
	enterOperator('+');
	resetCalculator();
	recallStoredInput(result);
	ck_assert_str_eq("", result->roman);
}
END_TEST

START_TEST (resetCalculator_clears_out_calculator_result)
{
	enterInput("XVIII");
	enterOperator('+');
	enterInput("XVIII");
	compute();
	resetCalculator();
	recallResult(result);
	ck_assert_str_eq("", result->roman);
}
END_TEST

Suite * make_calculator_suite(void) {
	Suite *s;
	TCase *tc_enter_input;
	TCase *tc_addition;
	TCase *tc_subtraction;
	TCase *tc_validation;

    s = suite_create("Calculator Tests");

	tc_enter_input = tcase_create("Entering Input");
	tcase_add_checked_fixture(tc_enter_input, setup_calculator_tests, teardown_calculator_tests);
	tcase_add_test(tc_enter_input, input_which_is_entered_is_stored_in_the_given_result_buffer);
	tcase_add_test(tc_enter_input, when_plus_operator_is_input_the_current_calculator_input_is_stored);
	tcase_add_test(tc_enter_input, when_minus_operator_is_input_the_current_calculator_input_is_stored);
	tcase_add_test(tc_enter_input, when_non_plus_or_minus_operator_is_input_an_error_is_stored);
	tcase_add_test(tc_enter_input, when_operator_is_input_before_valid_roman_input_error_is_stored);
	tcase_add_test(tc_enter_input, given_the_sequence_valid_input_plus_operator_valid_input_compute_the_addition_result_is_stored_in_calculatorResult);
	tcase_add_test(tc_enter_input, given_the_sequence_valid_input_minus_operator_valid_input_compute_the_subtraction_result_is_stored_in_calculatorResult);
	tcase_add_test(tc_enter_input, compute_sets_no_input_error_when_previous_result_is_not_stored);
	tcase_add_test(tc_enter_input, compute_sets_no_operator_error_when_valid_operator_is_not_stored);
	tcase_add_test(tc_enter_input, compute_sets_no_current_input_error_when_nothing_is_stored_in_current_input);
	tcase_add_test(tc_enter_input, operator_and_stored_input_and_current_input_are_reset_after_compute);
	tcase_add_test(tc_enter_input, resetCalculator_clears_out_current_input);
	tcase_add_test(tc_enter_input, resetCalculator_clears_out_stored_input);
	tcase_add_test(tc_enter_input, resetCalculator_clears_out_calculator_result);
	
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
	tcase_add_test(tc_validation, addition_with_a_result_greater_than_3999_results_in_error);
	tcase_add_test(tc_validation, addition_with_a_result_greater_than_3999_results_in_an_empty_result_value);
	tcase_add_test(tc_validation, subtraction_with_a_result_equal_to_zero_results_in_error);
	tcase_add_test(tc_validation, subtraction_with_a_result_equal_to_zero_results_in_an_empty_result_value);
	tcase_add_test(tc_validation, augend_which_fails_to_be_converted_to_int_should_return_empty_string_when_added);
	tcase_add_test(tc_validation, addend_which_fails_to_be_converted_to_int_should_return_empty_string_when_added);
	tcase_add_test(tc_validation, minuend_which_fails_to_be_converted_to_int_should_return_empty_string_when_subtracted);
	tcase_add_test(tc_validation, subtrahend_which_fails_to_be_converted_to_int_should_return_empty_string_when_subtracted);
    
    suite_add_tcase(s, tc_addition);
    suite_add_tcase(s, tc_subtraction);
    suite_add_tcase(s, tc_validation);
    suite_add_tcase(s, tc_enter_input);

    return s;
}
