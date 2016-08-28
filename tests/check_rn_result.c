#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <signal.h>

#include "check_suites.h"

#include "../src/rn_result.h"

RNResult *result;

void setup_rn_result_tests() {
	result = malloc(sizeof *result);
}

void teardown_rn_result_tests() {
	free(result);
}

START_TEST (initRNResult_sets_value_to_empty_string)
{
	initRNResult(result);
	
	ck_assert_str_eq("", result->value);
}
END_TEST

START_TEST (initRNResult_sets_error_to_0)
{
	initRNResult(result);
	
	ck_assert_uint_eq(0, result->error->number);
	ck_assert_str_eq("No Error", result->error->text);
	
	clearRNResult(result);
}
END_TEST

START_TEST (clearRNResult_sets_value_to_NULL)
{
	initRNResult(result);
	clearRNResult(result);
	
	ck_assert_ptr_eq(NULL, result->value);
}
END_TEST

START_TEST (clearRNResult_sets_error_to_NULL)
{
	initRNResult(result);
	clearRNResult(result);
	
	ck_assert_ptr_eq(NULL, result->error);
}
END_TEST

Suite * make_rn_result_suite(void) {
	Suite *s;
	TCase *tc_rn_result;

    s = suite_create("Roman Numeral Result Struct Tests");

    tc_rn_result = tcase_create("Convenience functions");
    tcase_add_checked_fixture(tc_rn_result, setup_rn_result_tests, teardown_rn_result_tests);
	tcase_add_test(tc_rn_result, initRNResult_sets_value_to_empty_string);
	tcase_add_test(tc_rn_result, initRNResult_sets_error_to_0);
    tcase_add_test(tc_rn_result, clearRNResult_sets_value_to_NULL);
    tcase_add_test(tc_rn_result, clearRNResult_sets_error_to_NULL);
    
    suite_add_tcase(s, tc_rn_result);

    return s;
}
